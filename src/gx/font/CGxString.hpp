#ifndef GX_C_GX_STRING_HPP
#define GX_C_GX_STRING_HPP

#include "gx/Types.hpp"
#include <cstdint>
#include <storm/Array.hpp>
#include <storm/List.hpp>
#include <tempest/Vector.hpp>

struct EMBEDDEDPARSEINFO;
class CGxFont;
class CGxVertexPCT;

struct VERT {
    C3Vector vc;
    C2Vector tc;
};

class TEXTLINETEXTURE {
    public:
        // Static functions
        static TEXTLINETEXTURE* NewTextLineTexture(void);
        static void Recycle(TEXTLINETEXTURE* ptr);

        // Member variables
        TSGrowableArray<VERT> m_vert;
        TSGrowableArray<CImVector> m_colors;

        // Member functions
        void WriteGeometry(CGxVertexPCT*, const CImVector&, const C2Vector&, const CImVector&, const C3Vector&, bool, bool, int32_t, int32_t);
};

class CGxString : public TSLinkedNode<CGxString> {
    public:
        // Static functions
        static CGxString* GetNewString(int32_t linkOnList);

        // Member variables
        TSLink<CGxString> m_fontStringLink;
        TSLink<CGxString> m_batchedStringLink;
        float m_requestedFontHeight = 0.02f;
        float m_currentFontHeight = 0.02f;
        C3Vector m_position;
        CImVector m_fontColor = { 0xFF, 0xFF, 0xFF, 0xFF };
        CImVector m_shadowColor = { 0x00, 0x00, 0x00, 0xFF };
        C2Vector m_shadowOffset = { 0.00125f, -0.00125f };
        float m_blockWidth = 1.0f;
        float m_blockHeight = 1.0f;
        CGxFont* m_currentFace = nullptr;
        char* m_text = nullptr;
        int32_t m_textLen = 0;
        EGxFontVJusts m_vertJust = GxVJ_Top;
        EGxFontHJusts m_horzJust = GxHJ_Left;
        float m_spacing = 0.0f;
        uint32_t m_flags = 0;
        uint32_t m_texturePagesUsed = 0;
        int32_t m_textureEvicted = 0;
        int32_t m_lastGradientStart = -1;
        int32_t m_lastGradientLength = -1;
        C3Vector m_viewTranslation;
        float m_scale = 1.0f;
        int32_t m_intB0 = 0;
        TEXTLINETEXTURE* m_textLines[8] = {};
        int32_t m_intD4 = 0;

        // Member functions
        ~CGxString();
        void AddShadow(const C2Vector& offset, const CImVector& color);
        uint32_t CalculateVertsNeeded(int32_t);
        bool CheckGeometry(void);
        void ClearInstanceData(void);
        void CreateGeometry(void);
        int32_t Initialize(float, const C3Vector&, float, float, CGxFont*, const char*, EGxFontVJusts, EGxFontHJusts, float, uint32_t, const CImVector&, float);
        void InitializeTextLine(const char*, uint32_t, CImVector&, const C3Vector&, uint32_t*, EMBEDDEDPARSEINFO&);
        void InitializeViewTranslation(void);
        void Recycle();
        void SetColor(const CImVector&);
        int32_t SetGradient(int32_t, int32_t);
        void SetStringPosition(const C3Vector& position);
        void Tick();
        void WriteGeometry(CGxVertexPCT*, int32_t, int32_t, int32_t);
};

#endif
