
class ST_AdminConfigEditSession
{
    string FileName;
    int ExpectedChunks;
    ref array<string> Chunks;

    void ST_AdminConfigEditSession()
    {
        FileName = "";
        ExpectedChunks = 0;
        Chunks = new array<string>;
    }
}

class ST_AdminConfigEditorService
{
    protected static ref ST_AdminConfigEditorService s_Instance;
    protected ref map<string, ref ST_AdminConfigEditSession> m_SaveSessions;
    protected ref array<string> m_AllowedFiles;
    protected string m_ConfigRoot;
    protected int m_ChunkSize;

    static ST_AdminConfigEditorService Get()
    {
        if (!s_Instance)
            s_Instance = new ST_AdminConfigEditorService();

        return s_Instance;
    }

    void ST_AdminConfigEditorService()
    {
        m_ConfigRoot = "$profile:ZombicideMods/SurvivorThoughts/Configs";
        m_ChunkSize = 7000;
        m_SaveSessions = new map<string, ref ST_AdminConfigEditSession>;
        m_AllowedFiles = new array<string>;

        m_AllowedFiles.Insert("00_Core_Admin_Output.json");
        m_AllowedFiles.Insert("01_Player_State_Personality.json");
        m_AllowedFiles.Insert("02_Messages_Survival.json");
        m_AllowedFiles.Insert("03_Actions_Damage_Combat.json");
        m_AllowedFiles.Insert("04_World_Environment.json");
        m_AllowedFiles.Insert("05_Items_Corpses.json");
        m_AllowedFiles.Insert("06_Social_Sanity_Journal.json");
        m_AllowedFiles.Insert("07_Admin_Diagnostics.json");
        m_AllowedFiles.Insert("08_Survivor_Story_System.json");
        m_AllowedFiles.Insert("09_Admin_Priority_Trigger_System.json");
    }

    bool IsEditorRPC(int rpcType)
    {
        if (rpcType == ST_JournalRPC.ST_RPC_ADMIN_CONFIG_LIST_REQUEST)
            return true;
        if (rpcType == ST_JournalRPC.ST_RPC_ADMIN_CONFIG_LOAD_REQUEST)
            return true;
        if (rpcType == ST_JournalRPC.ST_RPC_ADMIN_CONFIG_SAVE_BEGIN)
            return true;
        if (rpcType == ST_JournalRPC.ST_RPC_ADMIN_CONFIG_SAVE_CHUNK)
            return true;
        if (rpcType == ST_JournalRPC.ST_RPC_ADMIN_CONFIG_SAVE_COMMIT)
            return true;

        return false;
    }

    void HandleRPC(PlayerBase player, PlayerIdentity sender, int rpcType, ParamsReadContext ctx)
    {
        if (!GetGame() || !GetGame().IsServer() || !player || !sender)
            return;

        if (!ST_AdminPriorityTriggerSystem.Get().IsAdminAllowed(player))
        {
            SendResult(player, false, "Access denied.");
            return;
        }

        if (!player.GetIdentity() || player.GetIdentity().GetPlainId() != sender.GetPlainId())
        {
            SendResult(player, false, "Identity validation failed.");
            return;
        }

        if (rpcType == ST_JournalRPC.ST_RPC_ADMIN_CONFIG_LIST_REQUEST)
        {
            SendFileList(player);
            return;
        }

        if (rpcType == ST_JournalRPC.ST_RPC_ADMIN_CONFIG_LOAD_REQUEST)
        {
            string loadFile;
            if (!ctx.Read(loadFile))
                loadFile = "";

            SendConfig(player, loadFile);
            return;
        }

        if (rpcType == ST_JournalRPC.ST_RPC_ADMIN_CONFIG_SAVE_BEGIN)
        {
            string beginFile;
            int expectedChunks;

            if (!ctx.Read(beginFile))
                beginFile = "";
            if (!ctx.Read(expectedChunks))
                expectedChunks = 0;

            BeginSave(sender.GetPlainId(), beginFile, expectedChunks, player);
            return;
        }

        if (rpcType == ST_JournalRPC.ST_RPC_ADMIN_CONFIG_SAVE_CHUNK)
        {
            int chunkIndex;
            string chunkData;

            if (!ctx.Read(chunkIndex))
                chunkIndex = -1;
            if (!ctx.Read(chunkData))
                chunkData = "";

            ReceiveSaveChunk(sender.GetPlainId(), chunkIndex, chunkData, player);
            return;
        }

        if (rpcType == ST_JournalRPC.ST_RPC_ADMIN_CONFIG_SAVE_COMMIT)
        {
            CommitSave(sender.GetPlainId(), player);
            return;
        }
    }

    bool IsAllowedFile(string fileName)
    {
        if (fileName == "" || fileName.Contains("..") || fileName.Contains("/") || fileName.Contains("\\"))
            return false;

        foreach (string allowed : m_AllowedFiles)
        {
            if (allowed == fileName)
                return true;
        }

        return false;
    }

    void SendFileList(PlayerBase player)
    {
        ScriptRPC rpc = new ScriptRPC();
        rpc.Write(m_AllowedFiles.Count());

        foreach (string fileName : m_AllowedFiles)
            rpc.Write(fileName);

        rpc.Send(player, ST_JournalRPC.ST_RPC_ADMIN_CONFIG_LIST_RESPONSE, true, player.GetIdentity());
    }

    void SendConfig(PlayerBase player, string fileName)
    {
        if (!IsAllowedFile(fileName))
        {
            SendResult(player, false, "The requested config is not on the editor allow-list.");
            return;
        }

        string path = m_ConfigRoot + "/" + fileName;
        string content;

        if (!ReadTextFile(path, content))
        {
            SendResult(player, false, "Could not read " + fileName + ".");
            return;
        }

        int chunkCount = 1;
        if (content.Length() > 0)
            chunkCount = (content.Length() + m_ChunkSize - 1) / m_ChunkSize;

        ScriptRPC begin = new ScriptRPC();
        begin.Write(fileName);
        begin.Write(chunkCount);
        begin.Write(content.Length());
        begin.Send(player, ST_JournalRPC.ST_RPC_ADMIN_CONFIG_LOAD_BEGIN, true, player.GetIdentity());

        for (int i = 0; i < chunkCount; i++)
        {
            int start = i * m_ChunkSize;
            int remaining = content.Length() - start;
            int take = m_ChunkSize;

            if (remaining < take)
                take = remaining;
            if (take < 0)
                take = 0;

            string part = "";
            if (take > 0)
                part = content.Substring(start, take);

            ScriptRPC chunk = new ScriptRPC();
            chunk.Write(i);
            chunk.Write(part);
            chunk.Send(player, ST_JournalRPC.ST_RPC_ADMIN_CONFIG_LOAD_CHUNK, true, player.GetIdentity());
        }

        ScriptRPC finish = new ScriptRPC();
        finish.Write(fileName);
        finish.Send(player, ST_JournalRPC.ST_RPC_ADMIN_CONFIG_LOAD_END, true, player.GetIdentity());
    }

    void BeginSave(string adminId, string fileName, int expectedChunks, PlayerBase player)
    {
        if (!IsAllowedFile(fileName))
        {
            SendResult(player, false, "The selected config is not writable.");
            return;
        }

        if (expectedChunks <= 0 || expectedChunks > 128)
        {
            SendResult(player, false, "Invalid config payload size.");
            return;
        }

        ST_AdminConfigEditSession session = new ST_AdminConfigEditSession();
        session.FileName = fileName;
        session.ExpectedChunks = expectedChunks;

        for (int i = 0; i < expectedChunks; i++)
            session.Chunks.Insert("");

        m_SaveSessions.Set(adminId, session);
        SendResult(player, true, "Upload started for " + fileName + ".");
    }

    void ReceiveSaveChunk(string adminId, int chunkIndex, string chunkData, PlayerBase player)
    {
        ST_AdminConfigEditSession session = m_SaveSessions.Get(adminId);

        if (!session)
        {
            SendResult(player, false, "No active config upload.");
            return;
        }

        if (chunkIndex < 0 || chunkIndex >= session.ExpectedChunks)
        {
            SendResult(player, false, "Invalid config chunk index.");
            return;
        }

        if (chunkData.Length() > m_ChunkSize + 64)
        {
            SendResult(player, false, "Config chunk exceeded the permitted size.");
            return;
        }

        session.Chunks.Set(chunkIndex, chunkData);
    }

    void CommitSave(string adminId, PlayerBase player)
    {
        ST_AdminConfigEditSession session = m_SaveSessions.Get(adminId);

        if (!session)
        {
            SendResult(player, false, "No active config upload.");
            return;
        }

        string content = "";

        for (int i = 0; i < session.ExpectedChunks; i++)
            content += session.Chunks.Get(i);

        string validationError;
        if (!ValidateJsonText(content, validationError))
        {
            SendResult(player, false, "Save rejected: " + validationError);
            m_SaveSessions.Remove(adminId);
            return;
        }

        string target = m_ConfigRoot + "/" + session.FileName;
        string oldContent;

        if (!ReadTextFile(target, oldContent))
        {
            SendResult(player, false, "Could not read the existing config for backup.");
            m_SaveSessions.Remove(adminId);
            return;
        }

        string backupRoot = m_ConfigRoot + "/_Backups";
        if (!FileExist(backupRoot))
            MakeDirectory(backupRoot);

        string backupPath = backupRoot + "/" + session.FileName + ".before_ingame_edit.bak";
        if (!WriteTextFile(backupPath, oldContent))
        {
            SendResult(player, false, "Could not create the pre-edit backup.");
            m_SaveSessions.Remove(adminId);
            return;
        }

        string tempPath = target + ".st_edit.tmp";
        if (!WriteTextFile(tempPath, content))
        {
            SendResult(player, false, "Could not write the temporary config.");
            m_SaveSessions.Remove(adminId);
            return;
        }

        string verifyContent;
        if (!ReadTextFile(tempPath, verifyContent) || verifyContent != content)
        {
            DeleteFile(tempPath);
            SendResult(player, false, "Temporary config verification failed.");
            m_SaveSessions.Remove(adminId);
            return;
        }

        // Write the verified payload to the authoritative file.
        if (!WriteTextFile(target, content))
        {
            DeleteFile(tempPath);
            SendResult(player, false, "Could not replace the live config.");
            m_SaveSessions.Remove(adminId);
            return;
        }

        DeleteFile(tempPath);
        m_SaveSessions.Remove(adminId);

        SurvivorThoughtsManager.Get().LoadConfig();
        ST_AdminPriorityTriggerSystem.Get().LoadConfig();
        ST_AdminPriorityTriggerSystem.Get().ST_WriteMessageHealthReport();
        ST_AdminPriorityTriggerSystem.Get().ST_WriteTriggerCoverageReport();

        SendResult(player, true, session.FileName + " saved, backed up, validated, and reloaded.");
    }

    bool ReadTextFile(string path, out string content)
    {
        content = "";

        if (!FileExist(path))
            return false;

        FileHandle file = OpenFile(path, FileMode.READ);
        if (!file)
            return false;

        string line;
        bool first = true;

        while (FGets(file, line) > 0)
        {
            if (!first)
                content += "\n";

            content += line;
            first = false;
        }

        CloseFile(file);
        return true;
    }

    bool WriteTextFile(string path, string content)
    {
        FileHandle file = OpenFile(path, FileMode.WRITE);
        if (!file)
            return false;

        FPrint(file, content);
        CloseFile(file);
        return true;
    }

    bool ValidateJsonText(string content, out string error)
    {
        error = "";

        if (content == "")
        {
            error = "The document is empty.";
            return false;
        }

        int objectDepth = 0;
        int arrayDepth = 0;
        bool inString = false;
        bool escaped = false;

        for (int i = 0; i < content.Length(); i++)
        {
            string ch = content.Substring(i, 1);

            if (inString)
            {
                if (escaped)
                {
                    escaped = false;
                    continue;
                }

                if (ch == "\\")
                {
                    escaped = true;
                    continue;
                }

                if (ch == "\"")
                    inString = false;

                continue;
            }

            if (ch == "\"")
            {
                inString = true;
                continue;
            }

            if (ch == "{")
                objectDepth++;
            else if (ch == "}")
                objectDepth--;
            else if (ch == "[")
                arrayDepth++;
            else if (ch == "]")
                arrayDepth--;

            if (objectDepth < 0 || arrayDepth < 0)
            {
                error = "Closing bracket appears before its opening bracket.";
                return false;
            }
        }

        if (inString)
        {
            error = "An unterminated quoted string was found.";
            return false;
        }

        if (objectDepth != 0 || arrayDepth != 0)
        {
            error = "Object or array brackets are unbalanced.";
            return false;
        }

        string trimmed = content;
        trimmed.TrimInPlace();

        if (trimmed.Length() < 2 || trimmed.Substring(0, 1) != "{" || trimmed.Substring(trimmed.Length() - 1, 1) != "}")
        {
            error = "The root JSON value must be an object.";
            return false;
        }

        return true;
    }

    void SendResult(PlayerBase player, bool success, string message)
    {
        ScriptRPC rpc = new ScriptRPC();
        rpc.Write(success);
        rpc.Write(message);
        rpc.Send(player, ST_JournalRPC.ST_RPC_ADMIN_CONFIG_RESULT, true, player.GetIdentity());
    }
}
