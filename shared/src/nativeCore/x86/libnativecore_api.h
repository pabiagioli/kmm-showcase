#ifndef KONAN_LIBNATIVECORE_H
#define KONAN_LIBNATIVECORE_H
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
typedef bool            libnativecore_KBoolean;
#else
typedef _Bool           libnativecore_KBoolean;
#endif
typedef unsigned short     libnativecore_KChar;
typedef signed char        libnativecore_KByte;
typedef short              libnativecore_KShort;
typedef int                libnativecore_KInt;
typedef long long          libnativecore_KLong;
typedef unsigned char      libnativecore_KUByte;
typedef unsigned short     libnativecore_KUShort;
typedef unsigned int       libnativecore_KUInt;
typedef unsigned long long libnativecore_KULong;
typedef float              libnativecore_KFloat;
typedef double             libnativecore_KDouble;
typedef float __attribute__ ((__vector_size__ (16))) libnativecore_KVector128;
typedef void*              libnativecore_KNativePtr;
struct libnativecore_KType;
typedef struct libnativecore_KType libnativecore_KType;

typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_kotlin_Byte;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_kotlin_Short;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_kotlin_Int;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_kotlin_Long;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_kotlin_Float;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_kotlin_Double;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_kotlin_Char;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_kotlin_Boolean;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_kotlin_Unit;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_org_pampanet_mobile_audio_PitchDetector;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_org_pampanet_mobile_core_JniClass;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_org_pampanet_mobile_core_JniMethod;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_org_pampanet_mobile_core_JniObject;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_org_pampanet_mobile_core_CommonTools;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_kotlin_Number;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_kotlin_ByteArray;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_org_pampanet_mobile_core_FloatUtils;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_org_pampanet_mobile_core_Greeting;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_org_pampanet_mobile_core_JniBridge;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_kotlin_Array;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_kotlinx_cinterop_MemScope;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_kotlin_Any;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_org_pampanet_mobile_core_NdkBridge;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_org_pampanet_mobile_core_Platform;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_org_pampanet_mobile_core_Yin;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_kotlin_FloatArray;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_org_pampanet_mobile_pitch_PitchDetectionResult;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_org_pampanet_mobile_core_Yin_Companion;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_org_pampanet_mobile_pitch_McLeodPitchMethod;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_org_pampanet_mobile_pitch_McLeodPitchMethod_Companion;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_org_pampanet_mobile_pitch_Yin;
typedef struct {
  libnativecore_KNativePtr pinned;
} libnativecore_kref_org_pampanet_mobile_pitch_Yin_Companion;

extern libnativecore_KInt JNI_OnLoad(void* vm, void* preserved);
extern libnativecore_KInt Java_org_pampanet_mobile_core_FloatUtils_fromNativeSFloat(void* env, void* clazz, libnativecore_KFloat num);
extern libnativecore_KFloat Java_org_pampanet_mobile_core_FloatUtils_toNativeSFloat(void* env, void* clazz, void* byteArray, libnativecore_KInt offset);

typedef struct {
  /* Service functions. */
  void (*DisposeStablePointer)(libnativecore_KNativePtr ptr);
  void (*DisposeString)(const char* string);
  libnativecore_KBoolean (*IsInstance)(libnativecore_KNativePtr ref, const libnativecore_KType* type);
  libnativecore_kref_kotlin_Byte (*createNullableByte)(libnativecore_KByte);
  libnativecore_kref_kotlin_Short (*createNullableShort)(libnativecore_KShort);
  libnativecore_kref_kotlin_Int (*createNullableInt)(libnativecore_KInt);
  libnativecore_kref_kotlin_Long (*createNullableLong)(libnativecore_KLong);
  libnativecore_kref_kotlin_Float (*createNullableFloat)(libnativecore_KFloat);
  libnativecore_kref_kotlin_Double (*createNullableDouble)(libnativecore_KDouble);
  libnativecore_kref_kotlin_Char (*createNullableChar)(libnativecore_KChar);
  libnativecore_kref_kotlin_Boolean (*createNullableBoolean)(libnativecore_KBoolean);
  libnativecore_kref_kotlin_Unit (*createNullableUnit)(void);

  /* User functions. */
  struct {
    struct {
      void (*main)();
      struct {
        struct {
          struct {
            struct {
              struct {
                libnativecore_KType* (*_type)(void);
                libnativecore_kref_org_pampanet_mobile_audio_PitchDetector (*PitchDetector)(libnativecore_KFloat sampleRate, libnativecore_KInt bufferSize);
              } PitchDetector;
            } audio;
            struct {
              libnativecore_KInt (*JNI_OnLoad_)(void* vm, void* preserved);
              libnativecore_kref_org_pampanet_mobile_core_JniClass (*asJniClass)(void* jclass);
              libnativecore_kref_org_pampanet_mobile_core_JniMethod (*asJniMethod)(void* jmethodID);
              libnativecore_kref_org_pampanet_mobile_core_JniObject (*asJniObject)(void* jobject);
              libnativecore_KInt (*fromNativeSFloat)(void* env, void* clazz, libnativecore_KFloat num);
              void (*logError)(const char* tag, const char* message);
              void (*logInfo)(const char* tag, const char* message);
              libnativecore_KFloat (*toNativeSFloat)(void* env, void* clazz, void* byteArray, libnativecore_KInt offset);
              struct {
                libnativecore_KType* (*_type)(void);
                libnativecore_kref_org_pampanet_mobile_core_CommonTools (*_instance)();
                libnativecore_kref_kotlin_ByteArray (*numberToByteArray)(libnativecore_kref_org_pampanet_mobile_core_CommonTools thiz, libnativecore_kref_kotlin_Number data, libnativecore_KInt size);
              } CommonTools;
              struct {
                libnativecore_KType* (*_type)(void);
                libnativecore_kref_org_pampanet_mobile_core_FloatUtils (*_instance)();
                libnativecore_KInt (*fromSFloat)(libnativecore_kref_org_pampanet_mobile_core_FloatUtils thiz, libnativecore_KFloat num);
                libnativecore_KFloat (*toSFloat)(libnativecore_kref_org_pampanet_mobile_core_FloatUtils thiz, libnativecore_kref_kotlin_ByteArray byteArray, libnativecore_KInt offset);
              } FloatUtils;
              struct {
                libnativecore_KType* (*_type)(void);
                libnativecore_kref_org_pampanet_mobile_core_Greeting (*Greeting)();
                const char* (*greeting)(libnativecore_kref_org_pampanet_mobile_core_Greeting thiz);
              } Greeting;
              struct {
                libnativecore_KType* (*_type)(void);
                libnativecore_kref_org_pampanet_mobile_core_JniBridge (*JniBridge)(void* vm);
                void* (*get_fGetInt8ArrayElements)(libnativecore_kref_org_pampanet_mobile_core_JniBridge thiz);
                void* (*get_fPopLocalFrame)(libnativecore_kref_org_pampanet_mobile_core_JniBridge thiz);
                void* (*get_fPushLocalFrame)(libnativecore_kref_org_pampanet_mobile_core_JniBridge thiz);
                void* (*get_jniEnv)(libnativecore_kref_org_pampanet_mobile_core_JniBridge thiz);
                void* (*get_vm)(libnativecore_kref_org_pampanet_mobile_core_JniBridge thiz);
                libnativecore_kref_org_pampanet_mobile_core_JniObject (*CallObjectMethod)(libnativecore_kref_org_pampanet_mobile_core_JniBridge thiz, libnativecore_kref_org_pampanet_mobile_core_JniObject receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, libnativecore_kref_kotlin_Array arguments);
                void (*CallVoidMethod)(libnativecore_kref_org_pampanet_mobile_core_JniBridge thiz, libnativecore_kref_org_pampanet_mobile_core_JniObject receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, libnativecore_kref_kotlin_Array arguments);
                libnativecore_kref_org_pampanet_mobile_core_JniClass (*FindClass)(libnativecore_kref_org_pampanet_mobile_core_JniBridge thiz, const char* name);
                libnativecore_kref_org_pampanet_mobile_core_JniMethod (*GetMethodID)(libnativecore_kref_org_pampanet_mobile_core_JniBridge thiz, libnativecore_kref_org_pampanet_mobile_core_JniClass clazz, const char* name, const char* signature);
                libnativecore_kref_org_pampanet_mobile_core_JniObject (*toJString)(libnativecore_kref_org_pampanet_mobile_core_JniBridge thiz, const char* string);
                void* (*toJValues)(libnativecore_kref_org_pampanet_mobile_core_JniBridge thiz, libnativecore_kref_kotlin_Array arguments, libnativecore_kref_kotlinx_cinterop_MemScope scope);
              } JniBridge;
              struct {
                libnativecore_KType* (*_type)(void);
                libnativecore_kref_org_pampanet_mobile_core_JniClass (*JniClass)(void* jclass);
                void* (*get_jclass)(libnativecore_kref_org_pampanet_mobile_core_JniClass thiz);
                void* (*component1)(libnativecore_kref_org_pampanet_mobile_core_JniClass thiz);
                libnativecore_kref_org_pampanet_mobile_core_JniClass (*copy)(libnativecore_kref_org_pampanet_mobile_core_JniClass thiz, void* jclass);
                libnativecore_KBoolean (*equals)(libnativecore_kref_org_pampanet_mobile_core_JniClass thiz, libnativecore_kref_kotlin_Any other);
                libnativecore_KInt (*hashCode)(libnativecore_kref_org_pampanet_mobile_core_JniClass thiz);
                const char* (*toString)(libnativecore_kref_org_pampanet_mobile_core_JniClass thiz);
              } JniClass;
              struct {
                libnativecore_KType* (*_type)(void);
                libnativecore_kref_org_pampanet_mobile_core_JniMethod (*JniMethod)(void* jmethod);
                void* (*get_jmethod)(libnativecore_kref_org_pampanet_mobile_core_JniMethod thiz);
                void* (*component1)(libnativecore_kref_org_pampanet_mobile_core_JniMethod thiz);
                libnativecore_kref_org_pampanet_mobile_core_JniMethod (*copy)(libnativecore_kref_org_pampanet_mobile_core_JniMethod thiz, void* jmethod);
                libnativecore_KBoolean (*equals)(libnativecore_kref_org_pampanet_mobile_core_JniMethod thiz, libnativecore_kref_kotlin_Any other);
                libnativecore_KInt (*hashCode)(libnativecore_kref_org_pampanet_mobile_core_JniMethod thiz);
                const char* (*toString)(libnativecore_kref_org_pampanet_mobile_core_JniMethod thiz);
              } JniMethod;
              struct {
                libnativecore_KType* (*_type)(void);
                libnativecore_kref_org_pampanet_mobile_core_JniObject (*JniObject)(void* jobject);
                void* (*get_jobject)(libnativecore_kref_org_pampanet_mobile_core_JniObject thiz);
                void* (*component1)(libnativecore_kref_org_pampanet_mobile_core_JniObject thiz);
                libnativecore_kref_org_pampanet_mobile_core_JniObject (*copy)(libnativecore_kref_org_pampanet_mobile_core_JniObject thiz, void* jobject);
                libnativecore_KBoolean (*equals)(libnativecore_kref_org_pampanet_mobile_core_JniObject thiz, libnativecore_kref_kotlin_Any other);
                libnativecore_KInt (*hashCode)(libnativecore_kref_org_pampanet_mobile_core_JniObject thiz);
                const char* (*toString)(libnativecore_kref_org_pampanet_mobile_core_JniObject thiz);
              } JniObject;
              struct {
                libnativecore_KType* (*_type)(void);
                libnativecore_kref_org_pampanet_mobile_core_NdkBridge (*NdkBridge)(void* env);
                void* (*get_env)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz);
                void* (*get_fGetArrayLength)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz);
                void* (*get_fGetInt8ArrayElements)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz);
                void* (*get_fGetInt8ArrayRegion)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz);
                void* (*get_fNewByteArray)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz);
                void* (*get_fPopLocalFrame)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz);
                void* (*get_fPushLocalFrame)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz);
                libnativecore_kref_org_pampanet_mobile_core_JniObject (*callObjectMethod)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, libnativecore_kref_org_pampanet_mobile_core_JniObject receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, libnativecore_kref_kotlin_Array arguments);
                libnativecore_kref_org_pampanet_mobile_core_JniObject (*callObjectMethod_)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, libnativecore_kref_org_pampanet_mobile_core_JniObject receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, libnativecore_kref_kotlin_Array arguments);
                libnativecore_kref_org_pampanet_mobile_core_JniObject (*callObjectMethod__)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, libnativecore_kref_org_pampanet_mobile_core_JniObject receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, void* arguments);
                libnativecore_kref_org_pampanet_mobile_core_JniObject (*callObjectMethod___)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, void* receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, libnativecore_kref_kotlin_Array arguments);
                libnativecore_kref_org_pampanet_mobile_core_JniObject (*callObjectMethod____)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, void* receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, libnativecore_kref_kotlin_Array arguments);
                libnativecore_kref_org_pampanet_mobile_core_JniObject (*callObjectMethod_____)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, void* receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, void* arguments);
                libnativecore_kref_org_pampanet_mobile_core_JniObject (*callStaticObjectMethod)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, libnativecore_kref_org_pampanet_mobile_core_JniObject receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, libnativecore_kref_kotlin_Array arguments);
                libnativecore_kref_org_pampanet_mobile_core_JniObject (*callStaticObjectMethod_)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, libnativecore_kref_org_pampanet_mobile_core_JniObject receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, libnativecore_kref_kotlin_Array arguments);
                libnativecore_kref_org_pampanet_mobile_core_JniObject (*callStaticObjectMethod__)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, libnativecore_kref_org_pampanet_mobile_core_JniObject receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, void* arguments);
                libnativecore_kref_org_pampanet_mobile_core_JniObject (*callStaticObjectMethod___)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, void* receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, libnativecore_kref_kotlin_Array arguments);
                libnativecore_kref_org_pampanet_mobile_core_JniObject (*callStaticObjectMethod____)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, void* receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, libnativecore_kref_kotlin_Array arguments);
                libnativecore_kref_org_pampanet_mobile_core_JniObject (*callStaticObjectMethod_____)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, void* receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, void* arguments);
                void (*callStaticVoidMethod)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, libnativecore_kref_org_pampanet_mobile_core_JniClass receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, libnativecore_kref_kotlin_Array arguments);
                void (*callStaticVoidMethod_)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, libnativecore_kref_org_pampanet_mobile_core_JniClass receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, libnativecore_kref_kotlin_Array arguments);
                void (*callStaticVoidMethod__)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, libnativecore_kref_org_pampanet_mobile_core_JniClass receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, void* arguments);
                void (*callStaticVoidMethod___)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, void* receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, libnativecore_kref_kotlin_Array arguments);
                void (*callStaticVoidMethod____)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, void* receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, libnativecore_kref_kotlin_Array arguments);
                void (*callStaticVoidMethod_____)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, void* receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, void* arguments);
                void (*callVoidMethod)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, libnativecore_kref_org_pampanet_mobile_core_JniObject receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, libnativecore_kref_kotlin_Array arguments);
                void (*callVoidMethod_)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, libnativecore_kref_org_pampanet_mobile_core_JniObject receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, libnativecore_kref_kotlin_Array arguments);
                void (*callVoidMethod__)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, libnativecore_kref_org_pampanet_mobile_core_JniObject receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, void* arguments);
                void (*callVoidMethod___)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, void* receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, libnativecore_kref_kotlin_Array arguments);
                void (*callVoidMethod____)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, void* receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, libnativecore_kref_kotlin_Array arguments);
                void (*callVoidMethod_____)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, void* receiver, libnativecore_kref_org_pampanet_mobile_core_JniMethod method, void* arguments);
                libnativecore_kref_org_pampanet_mobile_core_JniClass (*findClass)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, const char* name);
                libnativecore_kref_org_pampanet_mobile_core_JniMethod (*getMethodID)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, libnativecore_kref_org_pampanet_mobile_core_JniClass clazz, const char* name, const char* signature);
                libnativecore_kref_org_pampanet_mobile_core_JniMethod (*getMethodID_)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, void* clazz, const char* name, const char* signature);
                libnativecore_kref_org_pampanet_mobile_core_JniClass (*getObjectClass)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, void* obj);
                libnativecore_kref_org_pampanet_mobile_core_JniMethod (*getStaticMethodID)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, libnativecore_kref_org_pampanet_mobile_core_JniClass clazz, const char* name, const char* signature);
                libnativecore_kref_org_pampanet_mobile_core_JniMethod (*getStaticMethodID_)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, void* clazz, const char* name, const char* signature);
                void* (*asJString)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, const char* thiz1);
                void* (*asJStringArray)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, libnativecore_kref_kotlin_Array thiz1);
                void* (*asJValues)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, libnativecore_kref_kotlin_Array thiz1, libnativecore_kref_kotlinx_cinterop_MemScope scope);
                const char* (*asKString)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, void* thiz1);
                libnativecore_kref_kotlin_Array (*asStringArray)(libnativecore_kref_org_pampanet_mobile_core_NdkBridge thiz, void* thiz1);
              } NdkBridge;
              struct {
                libnativecore_KType* (*_type)(void);
                libnativecore_kref_org_pampanet_mobile_core_Platform (*Platform)();
                const char* (*get_platform)(libnativecore_kref_org_pampanet_mobile_core_Platform thiz);
              } Platform;
              struct {
                libnativecore_KType* (*_type)(void);
                libnativecore_kref_org_pampanet_mobile_core_Yin (*Yin)(libnativecore_KFloat sampleRate, libnativecore_KInt bufferSize, libnativecore_KDouble threshold);
                libnativecore_kref_org_pampanet_mobile_pitch_PitchDetectionResult (*getPitch)(libnativecore_kref_org_pampanet_mobile_core_Yin thiz, libnativecore_kref_kotlin_FloatArray audioBuffer);
                struct {
                  libnativecore_KType* (*_type)(void);
                  libnativecore_kref_org_pampanet_mobile_core_Yin_Companion (*_instance)();
                  libnativecore_KInt (*get_DEFAULT_BUFFER_SIZE)(libnativecore_kref_org_pampanet_mobile_core_Yin_Companion thiz);
                  libnativecore_KInt (*get_DEFAULT_OVERLAP)(libnativecore_kref_org_pampanet_mobile_core_Yin_Companion thiz);
                } Companion;
              } Yin;
            } core;
            struct {
              struct {
                libnativecore_KType* (*_type)(void);
                libnativecore_kref_org_pampanet_mobile_pitch_McLeodPitchMethod (*McLeodPitchMethod)(libnativecore_KFloat sampleRate, libnativecore_KInt audioBufferSize, libnativecore_KDouble cutoffMPM);
                libnativecore_kref_org_pampanet_mobile_pitch_PitchDetectionResult (*getPitch)(libnativecore_kref_org_pampanet_mobile_pitch_McLeodPitchMethod thiz, libnativecore_kref_kotlin_FloatArray audioBuffer);
                struct {
                  libnativecore_KType* (*_type)(void);
                  libnativecore_kref_org_pampanet_mobile_pitch_McLeodPitchMethod_Companion (*_instance)();
                  libnativecore_KInt (*get_DEFAULT_BUFFER_SIZE)(libnativecore_kref_org_pampanet_mobile_pitch_McLeodPitchMethod_Companion thiz);
                  libnativecore_KInt (*get_DEFAULT_OVERLAP)(libnativecore_kref_org_pampanet_mobile_pitch_McLeodPitchMethod_Companion thiz);
                } Companion;
              } McLeodPitchMethod;
              struct {
                libnativecore_KType* (*_type)(void);
                libnativecore_kref_org_pampanet_mobile_pitch_PitchDetectionResult (*PitchDetectionResult)(libnativecore_KFloat pitch, libnativecore_KFloat probability, libnativecore_KBoolean pitched);
                libnativecore_KFloat (*get_pitch)(libnativecore_kref_org_pampanet_mobile_pitch_PitchDetectionResult thiz);
                void (*set_pitch)(libnativecore_kref_org_pampanet_mobile_pitch_PitchDetectionResult thiz, libnativecore_KFloat set);
                libnativecore_KBoolean (*get_pitched)(libnativecore_kref_org_pampanet_mobile_pitch_PitchDetectionResult thiz);
                void (*set_pitched)(libnativecore_kref_org_pampanet_mobile_pitch_PitchDetectionResult thiz, libnativecore_KBoolean set);
                libnativecore_KFloat (*get_probability)(libnativecore_kref_org_pampanet_mobile_pitch_PitchDetectionResult thiz);
                void (*set_probability)(libnativecore_kref_org_pampanet_mobile_pitch_PitchDetectionResult thiz, libnativecore_KFloat set);
                libnativecore_KFloat (*component1)(libnativecore_kref_org_pampanet_mobile_pitch_PitchDetectionResult thiz);
                libnativecore_KFloat (*component2)(libnativecore_kref_org_pampanet_mobile_pitch_PitchDetectionResult thiz);
                libnativecore_KBoolean (*component3)(libnativecore_kref_org_pampanet_mobile_pitch_PitchDetectionResult thiz);
                libnativecore_kref_org_pampanet_mobile_pitch_PitchDetectionResult (*copy)(libnativecore_kref_org_pampanet_mobile_pitch_PitchDetectionResult thiz, libnativecore_KFloat pitch, libnativecore_KFloat probability, libnativecore_KBoolean pitched);
                libnativecore_KBoolean (*equals)(libnativecore_kref_org_pampanet_mobile_pitch_PitchDetectionResult thiz, libnativecore_kref_kotlin_Any other);
                libnativecore_KInt (*hashCode)(libnativecore_kref_org_pampanet_mobile_pitch_PitchDetectionResult thiz);
                const char* (*toString)(libnativecore_kref_org_pampanet_mobile_pitch_PitchDetectionResult thiz);
              } PitchDetectionResult;
              struct {
                libnativecore_KType* (*_type)(void);
                libnativecore_kref_org_pampanet_mobile_pitch_Yin (*Yin)(libnativecore_KFloat sampleRate, libnativecore_KInt bufferSize, libnativecore_KDouble threshold);
                libnativecore_kref_org_pampanet_mobile_pitch_PitchDetectionResult (*getPitch)(libnativecore_kref_org_pampanet_mobile_pitch_Yin thiz, libnativecore_kref_kotlin_FloatArray audioBuffer);
                struct {
                  libnativecore_KType* (*_type)(void);
                  libnativecore_kref_org_pampanet_mobile_pitch_Yin_Companion (*_instance)();
                  libnativecore_KInt (*get_DEFAULT_BUFFER_SIZE)(libnativecore_kref_org_pampanet_mobile_pitch_Yin_Companion thiz);
                  libnativecore_KInt (*get_DEFAULT_OVERLAP)(libnativecore_kref_org_pampanet_mobile_pitch_Yin_Companion thiz);
                } Companion;
              } Yin;
            } pitch;
          } mobile;
        } pampanet;
      } org;
    } root;
  } kotlin;
} libnativecore_ExportedSymbols;
extern libnativecore_ExportedSymbols* libnativecore_symbols(void);
#ifdef __cplusplus
}  /* extern "C" */
#endif
#endif  /* KONAN_LIBNATIVECORE_H */
