#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "MelissaLookAndFeel.h"

// #define ENABLE_SHORTCUT_EDITOR

class MelissaPreferencesComponent : public Component
{
public:
    MelissaPreferencesComponent(AudioDeviceManager* audioDeviceManager);
    virtual ~MelissaPreferencesComponent();
    
    enum Tab
    {
        kTab_AudioMidi,
        kTab_KeyShortCut,
        kTab_MidiAssign,
        kNumOfTabs
    };
    void updateTab();
    
    // Component
    void paint(Graphics& graphics) override;
    void resized() override;
    
private:
    std::unique_ptr<ToggleButton> tabs_[kNumOfTabs];
    
    AudioDeviceManager* audioDeviceManager_;
    std::unique_ptr<AudioDeviceSelectorComponent> deviceComponent_;
    
    MelissaLookAndFeel lookAndFeel_;
    MelissaLookAndFeel_Tab lookAndFeelTab_;
};

