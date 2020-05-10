/*
  ==============================================================================

    Params.h
    Created: 2 May 2020 7:24:40pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Params
{
public:
    constexpr static const float MAX_DELAY = 1000.0f; //ms
    constexpr static const float MAX_MOD = 1.0f; //ms
    constexpr static const float MAX_SPREAD = 300.0f; //ms
    constexpr static const float MAX_OFFSET = 1.0f; //ratio of delay
    constexpr static const int MAX_TAPS = 10;
    constexpr static const float MIN_DELAY = MAX_MOD;
    // MAX_BUFFER represents the maximum amount of time (in ms) that a delay buffer must
    // hold in order to satisfy all possible parameter combinations.
    constexpr static const float MAX_BUFFER = MAX_DELAY * (1.0f + MAX_OFFSET) + MAX_SPREAD;
    
    inline static const String idDry = "dry";
    inline static const String idWet = "wet";
    inline static const String idBypass = "bypass";
    inline static const String idDelay = "delay";
    inline static const String idPan = "pan";
    inline static const String idTaps = "taps";
    inline static const String idSpread = "spread";
    inline static const String idOffsetLR = "offsetLR";
    inline static const String idAllpass = "allpass";
    inline static const String idFeedbackDirect = "feedbackDirect";
    inline static const String idFeedbackCross = "feedbackCross";
    inline static const String idHighPass = "idHighPass";
    inline static const String idLowPass = "idLowPass";
    inline static const String idModDepth = "idModDepth";
    inline static const String idModRate = "idModRate";

    static AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
    {
        std::vector<std::unique_ptr<RangedAudioParameter>> params;
        
        auto delayRange = NormalisableRange<float>(MIN_DELAY, MAX_DELAY);
        delayRange.setSkewForCentre(100.0f);
        
        auto gainRange = NormalisableRange<float>(-100.0f, 0.0f);
        gainRange.setSkewForCentre(-18.0f);
        
        auto frequencyRange = NormalisableRange<float>(20.0f, 20000.0f, 0.1f);
        frequencyRange.setSkewForCentre(640.0f);
        
        // auto tapsRange = NormalisableRange<float>(1.0f, 10.0f, 1.0f);
        
        auto modRateRange = NormalisableRange<float>(0.0f, 10.0f);
        modRateRange.setSkewForCentre(2.0f);
        
        auto spreadRange = NormalisableRange<float>(0.0f, 100.0f);
        spreadRange.setSkewForCentre(1.0f);
        
        params.push_back( std::make_unique<AudioParameterFloat>(idDry, "Dry Enabled", gainRange, 0.0f) );
        params.push_back( std::make_unique<AudioParameterFloat>(idWet, "Wet dB", gainRange, -6.0f) );
        params.push_back( std::make_unique<AudioParameterBool>(idBypass, "Matched Bypass", false) );
        params.push_back( std::make_unique<AudioParameterFloat>(idDelay, "Delay", delayRange, 100.0f) );
        params.push_back( std::make_unique<AudioParameterFloat>(idPan, "Pan", 0.0f, 1.0f, 0.5f));
        params.push_back( std::make_unique<AudioParameterInt>(idTaps, "Taps", 1, MAX_TAPS, 1) );
        params.push_back( std::make_unique<AudioParameterFloat>(idSpread, "Spread", spreadRange, 1.0f) );
        params.push_back( std::make_unique<AudioParameterFloat>(idOffsetLR, "L/R Offset", 0.0f, 1.0f, 0.5f ) );
        params.push_back( std::make_unique<AudioParameterBool>(idAllpass, "Allpass", false) );
        params.push_back( std::make_unique<AudioParameterFloat>(idFeedbackDirect, "Direct Feedback", 0.0f, 1.0f, 0.0f) );
        params.push_back( std::make_unique<AudioParameterFloat>(idFeedbackCross, "Cross Feedback", 0.0f, 1.0f, 0.0f) );
        params.push_back( std::make_unique<AudioParameterFloat>(idHighPass, "High Pass Hz", frequencyRange, 20.0f) );
        params.push_back( std::make_unique<AudioParameterFloat>(idLowPass, "Low Pass Hz", frequencyRange, 20000.0f) );
        params.push_back( std::make_unique<AudioParameterFloat>(idModDepth, "Mod Depth", 0.0f, 1.0f, 0.0f) );
        params.push_back( std::make_unique<AudioParameterFloat>(idModRate, "Mod Rate (Hz)", modRateRange, 2.0f) );
        
        return { params.begin(), params.end() };
    }
};
