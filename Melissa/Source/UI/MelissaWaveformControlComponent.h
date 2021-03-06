#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "MelissaDataSource.h"
#include "MelissaLabel.h"
#include "MelissaModel.h"

class MelissaWaveformControlComponent : public Component,
                                        public MelissaDataSourceListener,
                                        public Timer
                                        
{
public:
    MelissaWaveformControlComponent();
    virtual ~MelissaWaveformControlComponent();
    
    void resized() override;
    
    void timerCallback() override;
    
    void setPlayPosition(float ratio);
    void showTimeTooltip(float posRatio);
    
    // MelissaDataSourceListener
    void songChanged(const String& filePath, const float* buffer[], size_t bufferLength, int32_t sampleRate) override;
    
private:
    class WaveformView;
    
    std::unique_ptr<WaveformView> waveformView_;
    std::unique_ptr<MelissaLabel> posTooltip_;
    float timeSec_;
};
