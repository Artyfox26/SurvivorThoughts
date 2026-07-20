modded class MissionServer
{
    override void OnInit()
    {
        super.OnInit();

        if (GetGame() && GetGame().IsServer())
        {
            SurvivorThoughtsManager.Get().LoadConfig();
            ST_TrustLedger.Get().Start();
            ST_GasMaskFilterMonitor.Get().Start();
            SurvivorThoughtsManager.Get().Log("MissionServer init complete.");
        }
    }
}
