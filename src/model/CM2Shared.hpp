#ifndef MODEL_C_M2_SHARED_HPP
#define MODEL_C_M2_SHARED_HPP

#include "gx/Texture.hpp"
#include <cstdint>
#include <storm/String.hpp>
#include <tempest/Box.hpp>

class CAsyncObject;
class CGxBuf;
class CGxPool;
class CM2Cache;
class CM2Model;
class CShaderEffect;
class M2Batch;
class M2Data;
class M2SkinProfile;
class M2SkinSection;
class SFile;

class CM2Shared {
    public:
        // Static functions
        static void LoadFailedCallback(void* param);
        static void LoadSucceededCallback(void* param);
        static void SkinProfileLoadedCallback(void* param);

        // Member variables
        CM2Cache* m_cache;
        uint32_t m_m2DataLoaded : 1;
        uint32_t m_skinProfileLoaded : 1;
        uint32_t m_flag4 : 1;
        uint32_t m_flag8 : 1;
        uint32_t m_flag10 : 1;
        uint32_t m_flag20 : 1;
        uint32_t m_flag40 : 1;
        CAsyncObject* asyncObject = nullptr;
        CM2Model* m_callbackList = nullptr;
        CM2Model** m_callbackListTail = &this->m_callbackList;
        char m_filePath[STORM_MAX_PATH];
        char* ext = nullptr;
        M2Data* m_data = nullptr;
        CAaBox aaBox154;
        uint32_t m_dataSize = 0;
        M2SkinProfile* skinProfile = nullptr;
        HTEXTURE* textures = nullptr;
        CGxPool* m_indexPool = nullptr;
        CGxBuf* m_indexBuf = nullptr;
        CGxPool* m_vertexPool = nullptr;
        CGxBuf* m_vertexBuf = nullptr;
        CShaderEffect** m_batchShaders = nullptr;
        M2SkinSection* m_skinSections = nullptr;
        uint32_t uint190 = 0;
        uint32_t uint194 = 0;

        // Member functions
        CM2Shared(CM2Cache* cache)
            : m_cache(cache)
            , m_m2DataLoaded(0)
            , m_skinProfileLoaded(0)
            , m_flag4(0)
            , m_flag8(0)
            , m_flag10(0)
            , m_flag20(0)
            , m_flag40(0)
            {};
        void AddRef(void);
        int32_t CallbackWhenLoaded(CM2Model* model);
        CShaderEffect* CreateSimpleEffect(uint32_t textureCount, uint16_t shader, uint16_t textureCoordComboIndex);
        CShaderEffect* GetEffect(M2Batch* batch);
        int32_t FinishLoadingSkinProfile(uint32_t size);
        int32_t Initialize(void);
        int32_t InitializeSkinProfile(void);
        int32_t Load(SFile*, int32_t, CAaBox*);
        int32_t LoadSkinProfile(uint32_t profile);
        void Release(void);
        int32_t SetIndices(void);
        int32_t SetVertices(uint32_t a2);
        void SubstituteSimpleShaders(void);
        void SubstituteSpecializedShaders(void);
};

#endif
