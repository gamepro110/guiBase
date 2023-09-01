#pragma once

#include <guiBase/Layer.h>
#include <guiBase/Logger.h>

#include <memory>
#include <string>
#include <typeinfo>
#include <vector>

struct GLFWwindow;

namespace guiBase {
    struct WindowSettings {
        std::string name;
        int32_t width;
        int32_t height;
    };

    class App {
    public:
        App() = delete;
        explicit App(WindowSettings settings);
        App(const App&) = delete;
        App(App&&) noexcept = delete;
        ~App();

    public:
        App& operator=(const App&) = delete;
        App& operator=(const App&&) noexcept = delete;

    public:
        void run();
        void close();

        template<typename T>
        void PushLayer() {
            static_assert(std::is_base_of<Layer, T>::value, "Pushed type is not subclass of Layer!!");
            LOG_TRACE(std::string("adding ") + typeid(T).name() + " to layerstack");
            layerStack.emplace_back(std::make_shared<T>())->onAttach();
        }

        void PushLayer(const std::shared_ptr<Layer>& layer) {
            layerStack.emplace_back(layer);
            layer->onAttach();
            LOG_TRACE(std::string("added ") + typeid(*layer.get()).name() + " to layerstack");
        }

    private:
        void init();
        void shutdown();

    private:
        WindowSettings settings;
        GLFWwindow* windowHandle;
        std::vector<std::shared_ptr<Layer>> layerStack;
    };

    App* CreateApp(int argc, char** argv);
}// namespace guiBase
