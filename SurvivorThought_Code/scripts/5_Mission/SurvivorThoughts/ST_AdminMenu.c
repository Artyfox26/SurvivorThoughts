
class ST_AdminMenu : UIScriptedMenu
{
    protected static ST_AdminMenu s_ActiveMenu;

    protected TextWidget m_Title;
    protected TextWidget m_SelectedFileLabel;
    protected TextWidget m_StatusText;
    protected TextListboxWidget m_ConfigFileList;
    protected MultilineEditBoxWidget m_ConfigEditor;

    protected ButtonWidget m_LoadButton;
    protected ButtonWidget m_SaveButton;
    protected ButtonWidget m_RevertButton;
    protected ButtonWidget m_ReloadButton;
    protected ButtonWidget m_HealthButton;
    protected ButtonWidget m_CoverageButton;
    protected ButtonWidget m_CloseButton;

    protected string m_CurrentFile;
    protected string m_LastLoadedText;
    protected int m_ExpectedLoadChunks;
    protected ref array<string> m_LoadChunks;
    protected int m_SaveChunkSize;
    protected int m_LastFileListRevision;
    protected int m_LastContentRevision;
    protected int m_LastResultRevision;

    override Widget Init()
    {
        layoutRoot = GetGame().GetWorkspace().CreateWidgets("SurvivorThoughts/gui/layouts/survivorthoughts/st_admin_menu.layout");
        s_ActiveMenu = this;
        m_SaveChunkSize = 7000;

        ST_AdminConfigEditorClientState initialState = ST_AdminConfigEditorClientState.Get();
        m_LastFileListRevision = initialState.FileListRevision;
        m_LastContentRevision = initialState.ContentRevision;
        m_LastResultRevision = initialState.ResultRevision;

        m_Title = TextWidget.Cast(layoutRoot.FindAnyWidget("Title"));
        m_SelectedFileLabel = TextWidget.Cast(layoutRoot.FindAnyWidget("SelectedFileLabel"));
        m_StatusText = TextWidget.Cast(layoutRoot.FindAnyWidget("StatusText"));
        m_ConfigFileList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("ConfigFileList"));
        m_ConfigEditor = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("ConfigEditor"));

        m_LoadButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("LoadButton"));
        m_SaveButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("SaveButton"));
        m_RevertButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("RevertButton"));
        m_ReloadButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("ReloadButton"));
        m_HealthButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("HealthButton"));
        m_CoverageButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("CoverageButton"));
        m_CloseButton = ButtonWidget.Cast(layoutRoot.FindAnyWidget("CloseButton"));

        if (m_ConfigEditor)
            m_ConfigEditor.Enable(false);

        ST_SetStatus("Requesting server configuration list...");

        if (GetGame() && GetGame().GetInput())
            GetGame().GetInput().ChangeGameFocus(1);

        if (GetGame() && GetGame().GetUIManager())
            GetGame().GetUIManager().ShowCursor(true);

        ST_RequestConfigList();
        return layoutRoot;
    }



    override void Update(float timeslice)
    {
        super.Update(timeslice);

        ST_AdminConfigEditorClientState state = ST_AdminConfigEditorClientState.Get();

        if (state.FileListRevision != m_LastFileListRevision)
        {
            m_LastFileListRevision = state.FileListRevision;

            if (m_ConfigFileList)
            {
                m_ConfigFileList.ClearItems();

                foreach (string fileName : state.Files)
                    m_ConfigFileList.AddItem(fileName, NULL, 0);
            }

            ST_SetStatus(state.Files.Count().ToString() + " editable configuration files received.");
        }

        if (state.ContentRevision != m_LastContentRevision)
        {
            m_LastContentRevision = state.ContentRevision;
            m_CurrentFile = state.LoadedFile;
            m_LastLoadedText = state.LoadedContent;

            if (m_SelectedFileLabel)
                m_SelectedFileLabel.SetText(m_CurrentFile + " — " + m_LastLoadedText.Length().ToString() + " characters");

            if (m_ConfigEditor)
            {
                m_ConfigEditor.SetText(m_LastLoadedText);
                m_ConfigEditor.Enable(true);
            }

            ST_SetStatus(m_CurrentFile + " loaded. Edit carefully, then use Validate & Save.");
        }

        if (state.ResultRevision != m_LastResultRevision)
        {
            m_LastResultRevision = state.ResultRevision;

            if (state.ResultSuccess)
            {
                ST_SetStatus("SUCCESS: " + state.ResultMessage);

                if (m_CurrentFile != "")
                    ST_RequestConfig(m_CurrentFile);
            }
            else
            {
                ST_SetStatus("ERROR: " + state.ResultMessage);
            }
        }
    }

    override void OnHide()
    {
        super.OnHide();

        if (s_ActiveMenu == this)
            s_ActiveMenu = NULL;

        if (GetGame() && GetGame().GetInput())
            GetGame().GetInput().ResetGameFocus();
    }

    static ST_AdminMenu GetActive()
    {
        return s_ActiveMenu;
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (w == m_LoadButton)
        {
            ST_LoadSelected();
            return true;
        }

        if (w == m_SaveButton)
        {
            ST_SaveCurrent();
            return true;
        }

        if (w == m_RevertButton)
        {
            ST_RevertCurrent();
            return true;
        }

        if (w == m_ReloadButton)
        {
            ST_SendAdminCommand("RELOAD");
            ST_SetStatus("Reload request sent.");
            return true;
        }

        if (w == m_HealthButton)
        {
            ST_SendAdminCommand("HEALTH");
            ST_SetStatus("Message-health report requested.");
            return true;
        }

        if (w == m_CoverageButton)
        {
            ST_SendAdminCommand("COVERAGE");
            ST_SetStatus("Trigger-coverage report requested.");
            return true;
        }

        if (w == m_CloseButton)
        {
            ST_Close();
            return true;
        }

        return super.OnClick(w, x, y, button);
    }

    override bool OnDoubleClick(Widget w, int x, int y, int button)
    {
        if (w == m_ConfigFileList)
        {
            ST_LoadSelected();
            return true;
        }

        return super.OnDoubleClick(w, x, y, button);
    }

    void ST_RequestConfigList()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
            return;

        ScriptRPC rpc = new ScriptRPC();
        rpc.Send(player, ST_JournalRPC.ST_RPC_ADMIN_CONFIG_LIST_REQUEST, true, NULL);
    }

    void ST_LoadSelected()
    {
        if (!m_ConfigFileList)
            return;

        int row = m_ConfigFileList.GetSelectedRow();
        if (row < 0)
        {
            ST_SetStatus("Select a configuration file first.");
            return;
        }

        string fileName;
        m_ConfigFileList.GetItemText(row, 0, fileName);

        if (fileName == "")
        {
            ST_SetStatus("The selected row has no file name.");
            return;
        }

        ST_RequestConfig(fileName);
    }

    void ST_RequestConfig(string fileName)
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
            return;

        ST_SetStatus("Loading " + fileName + "...");

        ScriptRPC rpc = new ScriptRPC();
        rpc.Write(fileName);
        rpc.Send(player, ST_JournalRPC.ST_RPC_ADMIN_CONFIG_LOAD_REQUEST, true, NULL);
    }

    void ST_SaveCurrent()
    {
        if (m_CurrentFile == "" || !m_ConfigEditor)
        {
            ST_SetStatus("Load a configuration file before saving.");
            return;
        }

        string content;
        m_ConfigEditor.GetText(content);

        if (content == "")
        {
            ST_SetStatus("Save blocked: editor content is empty.");
            return;
        }

        int chunkCount = 1;
        if (content.Length() > 0)
            chunkCount = (content.Length() + m_SaveChunkSize - 1) / m_SaveChunkSize;

        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
            return;

        ST_SetStatus("Uploading " + m_CurrentFile + " for server validation...");

        ScriptRPC begin = new ScriptRPC();
        begin.Write(m_CurrentFile);
        begin.Write(chunkCount);
        begin.Send(player, ST_JournalRPC.ST_RPC_ADMIN_CONFIG_SAVE_BEGIN, true, NULL);

        for (int i = 0; i < chunkCount; i++)
        {
            int start = i * m_SaveChunkSize;
            int remaining = content.Length() - start;
            int take = m_SaveChunkSize;

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
            chunk.Send(player, ST_JournalRPC.ST_RPC_ADMIN_CONFIG_SAVE_CHUNK, true, NULL);
        }

        ScriptRPC commit = new ScriptRPC();
        commit.Send(player, ST_JournalRPC.ST_RPC_ADMIN_CONFIG_SAVE_COMMIT, true, NULL);
    }

    void ST_RevertCurrent()
    {
        if (m_CurrentFile == "")
        {
            ST_SetStatus("No configuration is loaded.");
            return;
        }

        if (m_ConfigEditor)
            m_ConfigEditor.SetText(m_LastLoadedText);

        ST_SetStatus("Reverted unsaved editor changes for " + m_CurrentFile + ".");
    }

    void ST_OnConfigList(ParamsReadContext ctx)
    {
        int count;
        if (!ctx.Read(count))
            count = 0;

        if (m_ConfigFileList)
            m_ConfigFileList.ClearItems();

        for (int i = 0; i < count; i++)
        {
            string fileName;
            if (!ctx.Read(fileName))
                fileName = "";

            if (fileName != "" && m_ConfigFileList)
                m_ConfigFileList.AddItem(fileName, NULL, 0);
        }

        ST_SetStatus(count.ToString() + " editable configuration files received. Double-click or select and load.");
    }

    void ST_OnConfigLoadBegin(ParamsReadContext ctx)
    {
        string fileName;
        int chunkCount;
        int totalLength;

        if (!ctx.Read(fileName))
            fileName = "";
        if (!ctx.Read(chunkCount))
            chunkCount = 0;
        if (!ctx.Read(totalLength))
            totalLength = 0;

        m_CurrentFile = fileName;
        m_ExpectedLoadChunks = chunkCount;
        m_LoadChunks = new array<string>;

        for (int i = 0; i < chunkCount; i++)
            m_LoadChunks.Insert("");

        if (m_SelectedFileLabel)
            m_SelectedFileLabel.SetText(fileName + " — " + totalLength.ToString() + " characters");

        ST_SetStatus("Receiving " + fileName + "...");
    }

    void ST_OnConfigLoadChunk(ParamsReadContext ctx)
    {
        int index;
        string data;

        if (!ctx.Read(index))
            index = -1;
        if (!ctx.Read(data))
            data = "";

        if (!m_LoadChunks || index < 0 || index >= m_LoadChunks.Count())
            return;

        m_LoadChunks.Set(index, data);
    }

    void ST_OnConfigLoadEnd(ParamsReadContext ctx)
    {
        string fileName;
        if (!ctx.Read(fileName))
            fileName = "";

        if (fileName != m_CurrentFile || !m_LoadChunks)
        {
            ST_SetStatus("Config transfer mismatch. Reload the file.");
            return;
        }

        string content = "";
        for (int i = 0; i < m_LoadChunks.Count(); i++)
            content += m_LoadChunks.Get(i);

        m_LastLoadedText = content;

        if (m_ConfigEditor)
        {
            m_ConfigEditor.SetText(content);
            m_ConfigEditor.Enable(true);
        }

        ST_SetStatus(fileName + " loaded. Edit carefully, then use Validate & Save.");
    }

    void ST_OnConfigResult(ParamsReadContext ctx)
    {
        bool success;
        string message;

        if (!ctx.Read(success))
            success = false;
        if (!ctx.Read(message))
            message = "";

        if (success)
        {
            ST_SetStatus("SUCCESS: " + message);

            if (m_CurrentFile != "")
                ST_RequestConfig(m_CurrentFile);
        }
        else
        {
            ST_SetStatus("ERROR: " + message);
        }
    }

    void ST_SetStatus(string text)
    {
        if (m_StatusText)
            m_StatusText.SetText(text);
    }

    void ST_SendAdminCommand(string command)
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
            return;

        ScriptRPC rpc = new ScriptRPC();
        rpc.Write(command);
        rpc.Send(player, ST_JournalRPC.ST_RPC_ADMIN_MENU_COMMAND, true, NULL);
    }

    void ST_Close()
    {
        if (GetGame() && GetGame().GetUIManager())
        {
            GetGame().GetUIManager().ShowCursor(false);
            GetGame().GetUIManager().Back();
        }
    }
}
