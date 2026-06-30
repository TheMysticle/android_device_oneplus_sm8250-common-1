#include <stdint.h>
#include <dlfcn.h>

extern "C" {
    // The A16 target function (mangled)
    // getRotationTransform(const CameraMetadata& staticInfo, int mirrorMode, bool enableTransformInverseDisplay, int32_t* transform)
    int _ZN7android11CameraUtils20getRotationTransformERKNS_14CameraMetadataEibPi(const void* staticInfo, int mirrorMode, bool enableTransformInverseDisplay, int32_t* transform);

    // The A14 shim function (mangled) that libcsextimpl.so will look for
    // getRotationTransform(const CameraMetadata& staticInfo, int mirrorMode, int32_t* transform)
    int _ZN7android11CameraUtils20getRotationTransformERKNS_14CameraMetadataEiPi(const void* staticInfo, int mirrorMode, int32_t* transform) {
        // Forward the call to the A16 function, defaulting the bool parameter to false
        return _ZN7android11CameraUtils20getRotationTransformERKNS_14CameraMetadataEibPi(staticInfo, mirrorMode, false, transform);
    }
}

#include <unordered_map>
#include <vector>
#include <set>
#include <string>

namespace android {
    class CameraMetadata {};
    template<typename T> class sp {};
    class NotificationListener {};
    class SessionStatsBuilder {};
    namespace hardware {
        namespace camera2 {
            namespace impl {
                class PhysicalCaptureResultInfo {};
                class CaptureResultExtras {};
            }
        }
    }
    namespace camera3 {
        struct camera_stream_buffer {};
        enum ERROR_BUF_STRATEGY { ERROR_BUF_RETURN };

        void returnOutputBuffers(
            bool,
            sp<NotificationListener>,
            const camera_stream_buffer*,
            size_t,
            long,
            long,
            bool,
            long,
            SessionStatsBuilder&,
            bool,
            const std::unordered_map<int, std::vector<unsigned long>>&,
            const hardware::camera2::impl::CaptureResultExtras&,
            ERROR_BUF_STRATEGY,
            int) {}

        struct CaptureOutputStates;
        void removeInFlightRequestIfReadyLocked(CaptureOutputStates&, int) {}

        void sendCaptureResult(
            CaptureOutputStates&,
            CameraMetadata&,
            hardware::camera2::impl::CaptureResultExtras&,
            CameraMetadata&,
            unsigned int,
            bool,
            bool,
            bool,
            const std::set<std::string>&,
            const std::vector<hardware::camera2::impl::PhysicalCaptureResultInfo>&) {}
    } // namespace camera3

    class CameraProviderManager {
    public:
        int getCameraCharacteristics(const std::string&, bool, CameraMetadata*) const;
    };

    int CameraProviderManager::getCameraCharacteristics(const std::string& id, bool overrideForPerfClass, CameraMetadata* characteristics) const {
        typedef int (*getCameraCharacteristics_t)(const CameraProviderManager*, const std::string&, bool, CameraMetadata*, int);
        static getCameraCharacteristics_t func = (getCameraCharacteristics_t) dlsym(RTLD_DEFAULT, "_ZNK7android21CameraProviderManager24getCameraCharacteristicsERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEbPNS_14CameraMetadataEi");
        if (func) {
            return func(this, id, overrideForPerfClass, characteristics, 0);
        }
        return -1; // UNKNOWN_ERROR
    }
} // namespace android
