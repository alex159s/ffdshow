#ifndef _TRENDEREDTEXTSUBTITLEWORD_H_
#define _TRENDEREDTEXTSUBTITLEWORD_H_

#include "Tfont.h"

class TrenderedTextSubtitleWord : public TrenderedSubtitleWordBase
{
private:
 TrenderedTextSubtitleWord *secondaryColoredWord;
 TrenderedSubtitleLines::TprintPrefs prefs;
 YUVcolorA m_bodyYUV,m_outlineYUV,m_shadowYUV;
 int baseline;
 int topOverhang,bottomOverhang,leftOverhang,rightOverhang;
 int m_outlineWidth,m_shadowSize,m_shadowMode;
 int dstOffset;
 mutable int oldFader;
 mutable unsigned int oldBodyYUVa,oldOutlineYUVa;
 template<int GDI_rendering_window> void drawShadow(
                        HDC hdc,
                        HBITMAP hbmp,
                        unsigned char *bmp16,
                        HGDIOBJ old,
                        double xscale,
                        const SIZE &sz,
                        unsigned int gdi_font_scale
                        );
 void updateMask(int fader = 1 << 16, int create = 1) const; // create: 0=update, 1=new, 2=update after copy (karaoke)
 unsigned char* blur(unsigned char *src,stride_t Idx,stride_t Idy,int startx,int starty,int endx, int endy, bool mild);
 unsigned int getShadowSize(LONG fontHeight, unsigned int gdi_font_scale);
 unsigned int getBottomOverhang(void);
 unsigned int getRightOverhang(void);
 unsigned int getTopOverhang(void);
 unsigned int getLeftOverhang(void);
public:
 TSubtitleProps props;
 // full rendering
 TrenderedTextSubtitleWord(
                        HDC hdc,
                        const wchar_t *s,
                        size_t strlens,
                        const YUVcolorA &YUV,
                        const YUVcolorA &outlineYUV,
                        const YUVcolorA &shadowYUV,
                        const TrenderedSubtitleLines::TprintPrefs &prefs,
                        LOGFONT lf,
                        double xscale,
                        TSubtitleProps Iprops,
                        unsigned int gdi_font_scale,
                        unsigned int GDI_rendering_window                  // Only 4 and 6 are supported (easy to add).
                        );
 // secondary (for karaoke)
 TrenderedTextSubtitleWord(
                        const TrenderedTextSubtitleWord &parent,
                        bool senondaryColor                       // to distinguish from default copy constructor
                        );
 ~TrenderedTextSubtitleWord();
 virtual void print(int startx, int starty, unsigned int dx[3],int dy[3],unsigned char *dstLn[3],const stride_t stride[3],const unsigned char *bmp[3],const unsigned char *msk[3],REFERENCE_TIME rtStart=REFTIME_INVALID) const;
 unsigned int alignXsize;
 void* (__cdecl *TtextSubtitlePrintY)  (const unsigned char* bmp,const unsigned char* outline,const unsigned char* shadow,const unsigned short *colortbl,const unsigned char* dst,const unsigned char* msk);
 void* (__cdecl *TtextSubtitlePrintUV) (const unsigned char* bmp,const unsigned char* outline,const unsigned char* shadow,const unsigned short *colortbl,const unsigned char* dstU,const unsigned char* dstV);
 void* (__cdecl *YV12_lum2chr_min)(const unsigned char* lum0,const unsigned char* lum1,unsigned char* chr);
 void* (__cdecl *YV12_lum2chr_max)(const unsigned char* lum0,const unsigned char* lum1,unsigned char* chr);
 virtual int get_ascent64() const;
 virtual int get_descent64() const;
 virtual int get_baseline() const;
 virtual int get_topOverhang() const {return topOverhang;}
 virtual int get_bottomOverhang() const {return bottomOverhang;}
 virtual int get_leftOverhang() const {return leftOverhang;}
 virtual int get_rightOverhang() const {return rightOverhang;}
 virtual size_t getMemorySize() const;
};


#endif //_TRENDEREDTEXTSUBTITLEWORD_H_