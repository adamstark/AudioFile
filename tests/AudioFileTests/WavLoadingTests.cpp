#ifndef WAV_LOADING_TESTS
#define WAV_LOADING_TESTS
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <vector>

#include "../../AudioFile.h"

// --------------------------------------------
// Test audio files: 44.1kHz Stereo
#include "test-headers/wav_stereo_8bit_44100.h"
#include "test-headers/wav_stereo_16bit_44100.h"
#include "test-headers/wav_stereo_24bit_44100.h"

// --------------------------------------------
// Test audio files: 48kHz Stereo
#include "test-headers/wav_stereo_8bit_48000.h"
#include "test-headers/wav_stereo_16bit_48000.h"
#include "test-headers/wav_stereo_24bit_48000.h"

// --------------------------------------------
// Test audio files: 44.1kHz Mono
//#include "test-headers/wav_mono_8bit_44100.h"
#include "test-headers/wav_mono_16bit_44100.h"

// --------------------------------------------
// Test audio files: 48kHz Mono
//#include "test-headers/wav_mono_8bit_48000.h"
#include "test-headers/wav_mono_16bit_48000.h"

//=============================================================
BOOST_AUTO_TEST_SUITE (WavLoadingTests)

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Stereo_8bit_44100)
{
    AudioFile<double> audioFile;
    bool loadedOK = audioFile.load ("test-audio/wav_stereo_8bit_44100.wav");
    
    BOOST_CHECK (loadedOK);
    BOOST_CHECK_EQUAL (audioFile.getNumSamplesPerChannel(), wav_stereo_8bit_44100::numSamplesPerChannel);
    BOOST_CHECK_EQUAL (audioFile.getBitDepth(), wav_stereo_8bit_44100::bitDepth);
    BOOST_CHECK_EQUAL (audioFile.getSampleRate(), wav_stereo_8bit_44100::sampleRate);
    BOOST_CHECK_EQUAL (audioFile.getNumChannels(), wav_stereo_8bit_44100::testBuffer.size());
    
    for (int i = 0; i < wav_stereo_8bit_44100::testBuffer[0].size(); i++)
    {
        for (int k = 0; k < audioFile.getNumChannels(); k++)
        {
            BOOST_CHECK_CLOSE (audioFile.samples[k][i], wav_stereo_8bit_44100::testBuffer[k][i], 0.00001);
        }
    }
}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Stereo_16bit_44100)
{
    AudioFile<double> audioFile;
    bool loadedOK = audioFile.load ("test-audio/wav_stereo_16bit_44100.wav");
    
    BOOST_CHECK (loadedOK);
    BOOST_CHECK_EQUAL (audioFile.getNumSamplesPerChannel(), wav_stereo_16bit_44100::numSamplesPerChannel);
    BOOST_CHECK_EQUAL (audioFile.getBitDepth(), wav_stereo_16bit_44100::bitDepth);
    BOOST_CHECK_EQUAL (audioFile.getSampleRate(), wav_stereo_16bit_44100::sampleRate);
    BOOST_CHECK_EQUAL (audioFile.getNumChannels(), wav_stereo_16bit_44100::testBuffer.size());
    
    for (int i = 0; i < wav_stereo_16bit_44100::testBuffer[0].size(); i++)
    {
        for (int k = 0; k < audioFile.getNumChannels(); k++)
        {
            BOOST_CHECK_CLOSE (audioFile.samples[k][i], wav_stereo_16bit_44100::testBuffer[k][i], 0.00001);
        }
    }
}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Stereo_24bit_44100)
{
    AudioFile<double> audioFile;
    bool loadedOK = audioFile.load ("test-audio/wav_stereo_24bit_44100.wav");
    
    BOOST_CHECK (loadedOK);
    BOOST_CHECK_EQUAL (audioFile.getNumSamplesPerChannel(), wav_stereo_24bit_44100::numSamplesPerChannel);
    BOOST_CHECK_EQUAL (audioFile.getBitDepth(), wav_stereo_24bit_44100::bitDepth);
    BOOST_CHECK_EQUAL (audioFile.getSampleRate(), wav_stereo_24bit_44100::sampleRate);
    BOOST_CHECK_EQUAL (audioFile.getNumChannels(), wav_stereo_24bit_44100::testBuffer.size());
    
    for (int i = 0; i < wav_stereo_24bit_44100::testBuffer[0].size(); i++)
    {
        for (int k = 0; k < audioFile.getNumChannels(); k++)
        {
            BOOST_CHECK_CLOSE (audioFile.samples[k][i], wav_stereo_24bit_44100::testBuffer[k][i], 0.00001);
        }
    }
}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Stereo_32bit_44100)
{
  AudioFile<double> audioFile;
  bool loadedOK = audioFile.load ("test-audio/wav_stereo_32bit_44100.wav");
  
  BOOST_CHECK (loadedOK);
  BOOST_CHECK_EQUAL (audioFile.getNumSamplesPerChannel(), 352800);
  BOOST_CHECK_EQUAL (audioFile.getBitDepth(), 32);
  BOOST_CHECK_EQUAL (audioFile.getSampleRate(), 44100);
  BOOST_CHECK_EQUAL (audioFile.getNumChannels(), 2);
  
  // Reference: read in through Matlab (first 64 samples)
  std::vector<std::vector<double>> reference {
    { 7.77244567871094e-05 ,  0.000145316123962402 },
    { 0.000439882278442383 ,  0.000302672386169434 },
    { 0.00674319267272949  ,  0.00612282752990723 },
    { 0.016382098197937    ,  0.0153152942657471 },
    { 0.0151487588882446   ,  0.0142148733139038 },
    { 0.00341582298278809  ,  0.00587213039398193 },
    { -0.0125023126602173  , -0.00357162952423096 },
    { -0.0217453241348267  , -0.0115010738372803 },
    { -0.022707462310791   , -0.0217818021774292 },
    { -0.017827033996582   , -0.0234956741333008 },
    { -0.00089371204376220 , -0.0021892786026001 },
    { 0.0107858180999756   ,  0.00936055183410645 },
    { 0.00766479969024658  ,  0.0019000768661499 },
    { -0.00178730487823486 , -0.0047607421875 },
    { -0.00629222393035889 , -0.000453710556030273 },
    { 0.00178396701812744  ,  0.0112038850784302 },
    { 0.0313527584075928   ,  0.0283315181732178 },
    { 0.0207730531692505   ,  0.0117709636688232 },
    { -0.022290825843811   , -0.0326575040817261 },
    { 0.00968170166015625  , -0.00387370586395264 },
    { -0.00373435020446777 , -0.00323045253753662 },
    { -0.0470277070999146  , -0.0545462369918823 },
    { 0.0142315626144409   ,  0.00163185596466064 },
    { 0.0251777172088623   ,  0.0433876514434814 },
    { -0.00247633457183838 ,  0.0187458992004395 },
    { 0.0208892822265625   ,  0.0335485935211182 },
    { -0.0109539031982422  ,  0.00750398635864258 },
    { -0.0392974615097046  , -0.0354713201522827 },
    { -0.00938189029693604 , -0.0357832908630371 },
    { -0.0166007280349731  , -0.0415679216384888 },
    { -0.053926944732666   , -0.0326246023178101 },
    { -0.0511249303817749  , -0.0796664953231812 },
    { 0.012263298034668    ,  0.00228583812713623 },
    { 0.103702783584595    ,  0.119603276252747 },
    { 0.105173587799072    ,  0.170729041099548 },
    { 0.061316967010498    ,  0.133585691452026 },
    { 0.107999563217163    ,  0.101216077804565 },
    { 0.0264698266983032   ,  0.123700022697449 },
    { -0.0883380174636841  ,  0.0142438411712646 },
    { -0.0407258272171021  , -0.0427062511444092 },
    { -0.0103473663330078  , -0.00744879245758057 },
    { -0.00884878635406494 ,  0.0219517946243286 },
    { 0.078632116317749    ,  0.0263230800628662 },
    { -0.0113770961761475  ,  0.0128881931304932 },
    { -0.0830408334732056  , -0.0314878225326538 },
    { 0.142681479454041    ,  0.0151617527008057 },
    { 0.0191718339920044   ,  0.00898754596710205 },
    { -0.0219069719314575  ,  0.00101673603057861 },
    { 0.0249385833740234   ,  0.0396249294281006 },
    { -0.0596954822540283  , -0.0273034572601318 },
    { 0.0529693365097046   ,  0.00769448280334473 },
    { -0.026525616645813   , -0.0628191232681274 },
    { 0.0403858423233032   , -0.0374784469604492 },
    { -0.00207006931304932 , -0.0513983964920044 },
    { 0.0385066270828247   ,  0.0237759351730347 },
    { 0.208563089370728    ,  0.180346012115479 },
    { 0.0995622873306274   ,  0.0979213714599609 },
    { 0.171254515647888    ,  0.214262962341309 },
    { 0.149603962898254    ,  0.149571657180786 },
    { 0.13909387588501     ,  0.128116130828857 },
    { 0.140897393226624    ,  0.241058707237244 },
    { 0.0962514877319336   ,  0.143865942955017 },
    { 0.0498672723770142   ,  0.0476465225219727 },
    { 0.0204880237579346   ,  0.0452275276184082 },
  };

  for (int i = 0; i < reference.size(); i++)
  {
    for (int k = 0; k < reference[0].size(); k++)
    {
      BOOST_CHECK_CLOSE (audioFile.samples[k][i], reference[i][k], 1e-5f);
    }
  }
}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Mono_8bit_44100)
{

}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Mono_16bit_44100)
{
    AudioFile<double> audioFile;
    bool loadedOK = audioFile.load ("test-audio/wav_mono_16bit_44100.wav");
    
    BOOST_CHECK (loadedOK);
    BOOST_CHECK_EQUAL (audioFile.getNumSamplesPerChannel(), wav_mono_16bit_44100::numSamplesPerChannel);
    BOOST_CHECK_EQUAL (audioFile.getBitDepth(), wav_mono_16bit_44100::bitDepth);
    BOOST_CHECK_EQUAL (audioFile.getSampleRate(), wav_mono_16bit_44100::sampleRate);
    BOOST_CHECK_EQUAL (audioFile.getNumChannels(), wav_mono_16bit_44100::numChannels);
    
    for (int i = 0; i < wav_mono_16bit_44100::testBuffer.size(); i++)
    {
        for (int k = 0; k < audioFile.getNumChannels(); k++)
        {
            BOOST_CHECK_CLOSE (audioFile.samples[k][i], wav_mono_16bit_44100::testBuffer[i], 0.00001);
        }
    }
}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Mono_24bit_44100)
{

}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Mono_32bit_44100)
{
  AudioFile<double> audioFile;
  bool loadedOK = audioFile.load ("test-audio/wav_mono_32bit_44100.wav");
  
  BOOST_CHECK (loadedOK);
  BOOST_CHECK_EQUAL (audioFile.getNumSamplesPerChannel(), 352800);
  BOOST_CHECK_EQUAL (audioFile.getBitDepth(), 32);
  BOOST_CHECK_EQUAL (audioFile.getSampleRate(), 44100);
  BOOST_CHECK_EQUAL (audioFile.getNumChannels(), 1);
  
  // Reference: read in through Matlab (first 64 samples)
  std::vector<double> reference {
    -3.0517578125e-05,    -0.0001220703125,    -0.001251220703125,    -0.002655029296875,    -0.003082275390625,    0.00384521484375,
    0.02276611328125,    0.032806396484375,    0.02392578125,    -0.006927490234375,    -0.044647216796875,    -0.03363037109375,
    0.013580322265625,    0.030853271484375,    0.017547607421875,    0.00823974609375,    0.004669189453125,    -0.00555419921875,
    -0.0089111328125,    -0.014495849609375,    -0.01409912109375,    -0.04644775390625,    -0.087615966796875,    -0.070159912109375,
    -0.066192626953125,    -0.03851318359375,    0.079010009765625,    -0.015350341796875,    0.08154296875,    0.04486083984375,
    0.1390380859375,    0.130859375,    0.13897705078125,    0.170257568359375,    0.177337646484375,    0.200958251953125,
    0.1513671875,    0.172027587890625,    0.06463623046875,    0.018524169921875,    -0.0003662109375,    -0.040283203125,
    0.0504150390625,    0.1331787109375,    -0.0211181640625,    0.0137939453125,    -0.061004638671875,    0.03656005859375,
    0.14935302734375,    -0.0780029296875,    -0.030181884765625,    -0.13665771484375,    0.083526611328125,    0.14727783203125,
    0.075286865234375,    0.043701171875,    0.04949951171875,    0.259674072265625,    0.239288330078125,    0.32977294921875,
    0.241302490234375,    0.261627197265625,    0.145355224609375,    0.16058349609375,
  };
  
  for (int i = 0; i < reference.size(); i++)
  {
    for (int k = 0; k < audioFile.getNumChannels(); k++)
    {
      BOOST_CHECK_CLOSE (audioFile.samples[k][i], reference[i], 1e-5f);
    }
  }
}


//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Stereo_8bit_48000)
{
    AudioFile<double> audioFile;
    bool loadedOK = audioFile.load ("test-audio/wav_stereo_8bit_48000.wav");
    
    BOOST_CHECK (loadedOK);
    BOOST_CHECK_EQUAL (audioFile.getNumSamplesPerChannel(), wav_stereo_8bit_48000::numSamplesPerChannel);
    BOOST_CHECK_EQUAL (audioFile.getBitDepth(), wav_stereo_8bit_48000::bitDepth);
    BOOST_CHECK_EQUAL (audioFile.getSampleRate(), wav_stereo_8bit_48000::sampleRate);
    BOOST_CHECK_EQUAL (audioFile.getNumChannels(), wav_stereo_8bit_48000::testBuffer.size());
    
    for (int i = 0; i < wav_stereo_8bit_48000::testBuffer[0].size(); i++)
    {
        for (int k = 0; k < audioFile.getNumChannels(); k++)
        {
            BOOST_CHECK_CLOSE (audioFile.samples[k][i], wav_stereo_8bit_48000::testBuffer[k][i], 0.001);
        }
    }
}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Stereo_16bit_48000)
{
    AudioFile<double> audioFile;
    bool loadedOK = audioFile.load ("test-audio/wav_stereo_16bit_48000.wav");
    
    BOOST_CHECK (loadedOK);
    BOOST_CHECK_EQUAL (audioFile.getNumSamplesPerChannel(), wav_stereo_16bit_48000::numSamplesPerChannel);
    BOOST_CHECK_EQUAL (audioFile.getBitDepth(), wav_stereo_16bit_48000::bitDepth);
    BOOST_CHECK_EQUAL (audioFile.getSampleRate(), wav_stereo_16bit_48000::sampleRate);
    BOOST_CHECK_EQUAL (audioFile.getNumChannels(), wav_stereo_16bit_48000::testBuffer.size());
    
    for (int i = 0; i < wav_stereo_16bit_48000::testBuffer[0].size(); i++)
    {
        for (int k = 0; k < audioFile.getNumChannels(); k++)
        {
            BOOST_CHECK_CLOSE (audioFile.samples[k][i], wav_stereo_16bit_48000::testBuffer[k][i], 0.001);
        }
    }
}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Stereo_24bit_48000)
{
    AudioFile<double> audioFile;
    bool loadedOK = audioFile.load ("test-audio/wav_stereo_24bit_48000.wav");
    
    BOOST_CHECK (loadedOK);
    BOOST_CHECK_EQUAL (audioFile.getNumSamplesPerChannel(), wav_stereo_24bit_48000::numSamplesPerChannel);
    BOOST_CHECK_EQUAL (audioFile.getBitDepth(), wav_stereo_24bit_48000::bitDepth);
    BOOST_CHECK_EQUAL (audioFile.getSampleRate(), wav_stereo_24bit_48000::sampleRate);
    BOOST_CHECK_EQUAL (audioFile.getNumChannels(), wav_stereo_24bit_48000::testBuffer.size());
    
    for (int i = 0; i < wav_stereo_24bit_48000::testBuffer[0].size(); i++)
    {
        for (int k = 0; k < audioFile.getNumChannels(); k++)
        {
            BOOST_CHECK_CLOSE (audioFile.samples[k][i], wav_stereo_24bit_48000::testBuffer[k][i], 0.00001);
        }
    }
}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Mono_8bit_48000)
{
    
}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Mono_16bit_48000)
{
    AudioFile<double> audioFile;
    bool loadedOK = audioFile.load ("test-audio/wav_mono_16bit_48000.wav");
    
    BOOST_CHECK (loadedOK);
    BOOST_CHECK_EQUAL (audioFile.getNumSamplesPerChannel(), wav_mono_16bit_48000::numSamplesPerChannel);
    BOOST_CHECK_EQUAL (audioFile.getBitDepth(), wav_mono_16bit_48000::bitDepth);
    BOOST_CHECK_EQUAL (audioFile.getSampleRate(), wav_mono_16bit_48000::sampleRate);
    BOOST_CHECK_EQUAL (audioFile.getNumChannels(), wav_mono_16bit_48000::numChannels);
    
    for (int i = 0; i < wav_mono_16bit_48000::testBuffer.size(); i++)
    {
        for (int k = 0; k < audioFile.getNumChannels(); k++)
        {
            BOOST_CHECK_CLOSE (audioFile.samples[k][i], wav_mono_16bit_48000::testBuffer[i], 0.00001);
        }
    }
}

//=============================================================
BOOST_AUTO_TEST_CASE (WavLoadingTests_Mono_24bit_48000)
{
    
}

BOOST_AUTO_TEST_SUITE_END()

#endif
