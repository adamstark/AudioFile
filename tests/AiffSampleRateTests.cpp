#include <doctest.h>
#include <AudioFile.h>

struct AiffSampleRateTestsTag {};

template<>
class AudioFileUnitTests<AiffSampleRateTestsTag>
{
public:
    template<class T>
    static inline AudioFile<T>* get(AudioFile<T>& aufile)
    {
      return &aufile;
    }

    template<class T>
    static inline uint32_t getSampleRate (AudioFile<T>& aufile, const std::vector<uint8_t>& fileData)
    {
        return aufile.getAiffSampleRate(fileData, 0);
    }

    template<class T>
    static inline void setSampleRate (AudioFile<T>& aufile, std::vector<uint8_t>& fileData, uint32_t sampleRate)
    {
        aufile.addSampleRateToAiffData(fileData, sampleRate);
    }
};

using AiffSampleRateTests = AudioFileUnitTests<AiffSampleRateTestsTag>;

//=============================================================
TEST_SUITE ("Aiff Sample Rate Tests")
{
    //=============================================================
    TEST_CASE ("GeneralTests::CopyConstructor")
    {
        struct SampleRateInfo
        {
            uint32_t sampleRate;
            std::vector<uint8_t> data;
        };

        std::vector<SampleRateInfo> sampleRates =
        {
            { 8000,    { 64, 11, 250,   0, 0, 0, 0, 0, 0, 0 } },
            { 11025,   { 64, 12, 172,  68, 0, 0, 0, 0, 0, 0 } },
            { 16000,   { 64, 12, 250,   0, 0, 0, 0, 0, 0, 0 } },
            { 22050,   { 64, 13, 172,  68, 0, 0, 0, 0, 0, 0 } },
            { 32000,   { 64, 13, 250,   0, 0, 0, 0, 0, 0, 0 } },
            { 37800,   { 64, 14, 147, 168, 0, 0, 0, 0, 0, 0 } },
            { 44056,   { 64, 14, 172,  24, 0, 0, 0, 0, 0, 0 } },
            { 44100,   { 64, 14, 172,  68, 0, 0, 0, 0, 0, 0 } },
            { 47250,   { 64, 14, 184, 146, 0, 0, 0, 0, 0, 0 } },
            { 48000,   { 64, 14, 187, 128, 0, 0, 0, 0, 0, 0 } },
            { 50000,   { 64, 14, 195,  80, 0, 0, 0, 0, 0, 0 } },
            { 50400,   { 64, 14, 196, 224, 0, 0, 0, 0, 0, 0 } },
            { 88200,   { 64, 15, 172,  68, 0, 0, 0, 0, 0, 0 } },
            { 96000,   { 64, 15, 187, 128, 0, 0, 0, 0, 0, 0 } },
            { 176400,  { 64, 16, 172,  68, 0, 0, 0, 0, 0, 0 } },
            { 192000,  { 64, 16, 187, 128, 0, 0, 0, 0, 0, 0 } },
            { 352800,  { 64, 17, 172,  68, 0, 0, 0, 0, 0, 0 } },
            { 2822400, { 64, 20, 172,  68, 0, 0, 0, 0, 0, 0 } },
            { 5644800, { 64, 21, 172,  68, 0, 0, 0, 0, 0, 0 } }
        };

        AudioFile<float> aufile;

        // Convert IEEE 80 bits to uint32_t.
        for(const SampleRateInfo& info : sampleRates)
        {
            REQUIRE_EQ(AiffSampleRateTests::getSampleRate(aufile, info.data), info.sampleRate);
        }

        // Convert uint32_t to IEEE 80 bits.
        for(const SampleRateInfo& info : sampleRates)
        {
            std::vector<uint8_t> data;
            AiffSampleRateTests::setSampleRate(aufile, data, info.sampleRate);
            REQUIRE_EQ(data, info.data);
        }
    }
}
