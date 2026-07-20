
class ST_AdminConfigEditorClientState
{
    protected static ref ST_AdminConfigEditorClientState s_Instance;

    ref array<string> Files;
    string LoadingFile;
    string LoadedFile;
    string LoadedContent;
    int ExpectedChunks;
    ref array<string> LoadChunks;
    string ResultMessage;
    bool ResultSuccess;
    int FileListRevision;
    int ContentRevision;
    int ResultRevision;

    static ST_AdminConfigEditorClientState Get()
    {
        if (!s_Instance)
            s_Instance = new ST_AdminConfigEditorClientState();

        return s_Instance;
    }

    void ST_AdminConfigEditorClientState()
    {
        Files = new array<string>;
        LoadChunks = new array<string>;
    }

    void OnFileList(ParamsReadContext ctx)
    {
        int count;
        if (!ctx.Read(count))
            count = 0;

        Files.Clear();

        for (int i = 0; i < count; i++)
        {
            string fileName;
            if (!ctx.Read(fileName))
                fileName = "";

            if (fileName != "")
                Files.Insert(fileName);
        }

        FileListRevision++;
    }

    void OnLoadBegin(ParamsReadContext ctx)
    {
        int totalLength;

        if (!ctx.Read(LoadingFile))
            LoadingFile = "";
        if (!ctx.Read(ExpectedChunks))
            ExpectedChunks = 0;
        if (!ctx.Read(totalLength))
            totalLength = 0;

        LoadChunks = new array<string>;

        for (int i = 0; i < ExpectedChunks; i++)
            LoadChunks.Insert("");
    }

    void OnLoadChunk(ParamsReadContext ctx)
    {
        int index;
        string data;

        if (!ctx.Read(index))
            index = -1;
        if (!ctx.Read(data))
            data = "";

        if (!LoadChunks || index < 0 || index >= LoadChunks.Count())
            return;

        LoadChunks.Set(index, data);
    }

    void OnLoadEnd(ParamsReadContext ctx)
    {
        string fileName;
        if (!ctx.Read(fileName))
            fileName = "";

        if (fileName != LoadingFile || !LoadChunks)
            return;

        LoadedFile = fileName;
        LoadedContent = "";

        for (int i = 0; i < LoadChunks.Count(); i++)
            LoadedContent += LoadChunks.Get(i);

        ContentRevision++;
    }

    void OnResult(ParamsReadContext ctx)
    {
        if (!ctx.Read(ResultSuccess))
            ResultSuccess = false;
        if (!ctx.Read(ResultMessage))
            ResultMessage = "";

        ResultRevision++;
    }
}
