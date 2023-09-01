#include "exampleLayer.h"

#include "guiBase/App.h"
#include "guiBase/Layer.h"
#include "guiBase/Logger.h"
#include "guiBase/entrypoint.h"

bool guiBase::gRunning = true;

#if DEBUG
#include "imgui.h"
#include <cstdlib>

class demoLayer : public guiBase::Layer {
public:
    demoLayer() = default;
    ~demoLayer() = default;

public:
    void onAttach() override {
        LOG_TRACE("attaching demoLayer");
    }

    void onUpdate() override {
        ImGui::ShowDemoWindow(&showWindow);
    }

    void onDetach() override {
        LOG_TRACE("detaching demoLayer");
    }

private:
    void showConfigVal(const char* text, bool val) {
        ImGui::Checkbox(text, &val);
    }

private:
    bool showWindow{ true };
};
#endif

guiBase::App* guiBase::CreateApp(int argc, char** argv) {
    UNUSED(argc);
    UNUSED(argv);

    Logger::setLogLevel(LogLevel::trace);

    WindowSettings settings;

    settings.name = "example name";
    settings.width = 800;
    settings.height = 600;

    LOG_TRACE("creating app*");
    guiBase::App* app = new guiBase::App(settings);

    LOG_TRACE("adding layers");
    app->PushLayer<exampleLayer>();
#if DEBUG
    app->PushLayer<demoLayer>();
#endif

    return app;
}
