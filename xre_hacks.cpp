////////////////////////////////////////////////////////////////////////////////////////////
// Flinging a site by sending a sequense of XRE-commands
////////////////////////////////////////////////////////////////////////////////////////////
gGraphicsView->showMessage("Flinging site");

QString cmds[] =
{
      "{\"appId\":1,\"commandIndex\":914,\"command\":\"NEW\",\"targetId\":2327,\"targetPath\":null,\"klass\":\"XREView\",\"id\":2327,\"params\":{\"matrix\":[1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0],\"dimensions\":[1280.0,720.0],\"parent\":2,\"resourceOptions\":{\"textWrap\":\"NONE\",\"verticalAlign\":\"TOP\",\"horizontalAlign\":\"LEFT\",\"stretch\":\"NONE\",\"textTruncStyle\":\"NONE\",\"textStartPos\":[0.0,0.0],\"textStopPos\":[0.0,0.0],\"textStartChar\":0,\"textStopChar\":-1},\"alpha\":1.0,\"visible\":true,\"clip\":false,\"painting\":true,\"ignoreMouse\":false,\"paintPropertyDisabled\":true,\"punchThrough\":false}}"
    , "{\"appId\":1,\"commandIndex\":915,\"command\":\"NEW\",\"targetId\":2328,\"targetPath\":null,\"klass\":\"XREHTMLView\",\"id\":2328,\"params\":{\"url\":\"http://www.funnyordie.com/googletv/\",\"contentType\":null,\"position\":0,\"speed\":1.0,\"navigationMode\":null,\"enableServiceManager\":false,\"headers\":null,\"cookies\":null,\"options\":null,\"urlpatterns\":null,\"keymaps\":null,\"cookieJar\":null,\"servicesACL\":null,\"headers2\":null,\"renderer\":null}}"
    , "{\"appId\":1,\"commandIndex\":916,\"command\":\"SET\",\"targetId\":2327,\"targetPath\":null,\"props\":{\"resource\":2328}}"
    , "{\"appId\":1,\"commandIndex\":917,\"command\":\"NEW\",\"targetId\":2329,\"targetPath\":null,\"klass\":\"XREView\",\"id\":2329,\"params\":{\"matrix\":[1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0,100.0,100.0,0.0,1.0],\"dimensions\":[100.0,100.0],\"parent\":2,\"resourceOptions\":{\"textWrap\":\"NONE\",\"verticalAlign\":\"TOP\",\"horizontalAlign\":\"LEFT\",\"stretch\":\"NONE\",\"textTruncStyle\":\"NONE\",\"textStartPos\":[0.0,0.0],\"textStopPos\":[0.0,0.0],\"textStartChar\":0,\"textStopChar\":-1},\"alpha\":1.0,\"visible\":true,\"clip\":false,\"painting\":true,\"ignoreMouse\":false,\"paintPropertyDisabled\":true,\"punchThrough\":false}}"
    , "{\"appId\":1,\"commandIndex\":918,\"command\":\"NEW\",\"targetId\":2330,\"targetPath\":null,\"klass\":\"XREText\",\"id\":2330,\"params\":{\"text\":\"http://www.funnyordie.com/googletv/\",\"font\":2054,\"color\":-1,\"size\":15,\"leading\":null,\"blinkingCursor\":false}}"
    , "{\"appId\":1,\"commandIndex\":919,\"command\":\"SET\",\"targetId\":2329,\"targetPath\":null,\"props\":{\"resource\":2330}}"
    , "{\"appId\":1,\"callGUID\":\"\",\"command\":\"CALL\",\"commandIndex\":923,\"method\":\"activate\",\"params\":[],\"targetId\":2327,\"targetPath\":null}"
};

for(int i=0; i<ARRAY_LEN(cmds); i++)
{
    QString cmd = cmds[i];
    XRELOG_LOG("injecting command [%s]", cmd.toAscii().constData());
    XREGraphicsScene::GetInstance()->getRootApp()->GetConnection()->injectCommand(cmd);
}

////////////////////////////////////////////////////////////////////////////////////////////
// Dumping XRE-traffic
////////////////////////////////////////////////////////////////////////////////////////////
void CXREApplication::pushJSON(const char* data, size_t len)
{
    printf("CXREApplication::pushJSON(): command = ' '%s'\n", data);
    ...
}
