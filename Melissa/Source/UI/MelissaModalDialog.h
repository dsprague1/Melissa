#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "MelissaButtons.h"
#include "MelissaUISettings.h"
#include "MelissaHost.h"

class MelissaDialog : public Component
{
public:
    MelissaDialog(std::shared_ptr<Component> contentComponent, const String& title, bool closeOnClickingOutside);
    void paint(Graphics& g) override;
    void resized() override;
    
private:
    std::unique_ptr<BackgroundButton> backgroundButton_;
    std::unique_ptr<CloseButton> closeButton_;
    std::unique_ptr<Label> titleLabel_;
    std::shared_ptr<Component> contentComponent_;
    bool closeOnClickingOutside_;
};

class MelissaModalDialog
{
public:
    MelissaModalDialog() {}
    
    static void setParentComponent(Component* parentComponent) { parentComponent_ = parentComponent; }
    static void show(std::shared_ptr<Component> component, const String& title, bool closeOnClickingOutside = true);
    static void close();
    
private:
    static Component* parentComponent_;
    static std::unique_ptr<MelissaDialog> dialog_;
};
