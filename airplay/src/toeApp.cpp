#include "toeApp.h"
#include "TinyOpenEngine.h"
#include "s3eConfig.h"

using namespace TinyOpenEngine;

CtoeApp::CtoeApp()
{
}

CtoeApp::~CtoeApp()
{
}

void CtoeApp::Run()
{
	char startgroup [S3E_CONFIG_STRING_MAX];
	if (S3E_RESULT_SUCCESS == s3eConfigGetString("TOE", "startgroup", startgroup))
	{
		toeOpenGroupWorld("./menu/mainmenu.group");
	}
}
