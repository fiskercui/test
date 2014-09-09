
#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"

#include "codeIDE/runtime/Runtime.h"
#include "codeIDE/ConfigParser.h"

#include "PlayerProtocol.h"

using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    if (_project.getDebuggerType() == kCCLuaDebuggerCodeIDE)
    {
        initRuntime(_project.getProjectDir());
        if (!ConfigParser::getInstance()->isInit())
        {
            ConfigParser::getInstance()->readConfig();
        }
    }

    // initialize director
    auto director = Director::getInstance();
    director->setProjection(Director::Projection::_2D);
    auto glview = director->getOpenGLView();

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
   
    // register lua engine
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    
    StartupCall *call = StartupCall::create(this);
    if (_project.getDebuggerType() == kCCLuaDebuggerLDT)
    {
        auto scene = Scene::create();
        auto label = Label::createWithSystemFont("WAITING FOR CONNECT TO DEBUGGER...", "Arial", 32);
        const Size winSize = director->getWinSize();
        label->setPosition(winSize.width / 2, winSize.height / 2);
        scene->addChild(label);
        director->runWithScene(scene);
        scene->runAction(CallFunc::create(bind(&StartupCall::startup, *call)));
    }
    else
    {
        call->startup();
    }
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
}

void AppDelegate::setProjectConfig(const ProjectConfig& project)
{
    _project = project;
}

// ----------------------------------------

StartupCall *StartupCall::create(AppDelegate *app)
{
    StartupCall *call = new StartupCall();
    call->_app = app;
    call->autorelease();
    return call;
}

void StartupCall::startup()
{
    auto engine = LuaEngine::getInstance();
    auto stack = engine->getLuaStack();
    
    const ProjectConfig &project = _app->_project;
    
    // set search path
    string path = FileUtils::getInstance()->fullPathForFilename(project.getScriptFileRealPath().c_str());
    size_t pos;
    while ((pos = path.find_first_of("\\")) != std::string::npos)
    {
        path.replace(pos, 1, "/");
    }
    size_t p = path.find_last_of("/");
    string workdir;
    if (p != path.npos)
    {
        workdir = path.substr(0, p);
        stack->addSearchPath(workdir.c_str());
    }
    
    // connect debugger
    if (project.getDebuggerType() != kCCLuaDebuggerNone)
    {
        stack->connectDebugger(project.getDebuggerType(), NULL, 0, NULL, workdir.c_str());
    }
    
    // load framework
    if (project.isLoadPrecompiledFramework())
    {
        const string precompiledFrameworkPath = SimulatorConfig::getInstance()->getPrecompiledFrameworkPath();
        stack->loadChunksFromZIP(precompiledFrameworkPath.c_str());
    }

    // Code IDE
    if (project.getDebuggerType() == kCCLuaDebuggerCodeIDE)
    {
        if (startRuntime()) return;
    }

    // set default scene
    Scene *scene = Scene::create();
    if (Director::getInstance()->getRunningScene()) 
    {
        Director::getInstance()->replaceScene(scene);
    }
    else
    {
        Director::getInstance()->runWithScene(scene);
    }
    
    // load script
    string env = "__LUA_STARTUP_FILE__=\"";
    env.append(path);
    env.append("\"");
    engine->executeString(env.c_str());
    
    CCLOG("------------------------------------------------");
    CCLOG("LOAD LUA FILE: %s", path.c_str());
    CCLOG("------------------------------------------------");
    engine->executeScriptFile(path.c_str());
    
    // track start event
    player::PlayerProtocol::getInstance()->trackEvent("launch");
}
