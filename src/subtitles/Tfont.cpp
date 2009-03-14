/*
 * Copyright (c) 2002-2006 Milan Cutka
 *               2007-2009 h.yamagata
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "stdafx.h"
#include "Tconfig.h"
#include "TrenderedTextSubtitleWord.h"
#include "TfontSettings.h"
#include "IffdshowBase.h"
#include "simd.h"
#include "TsubreaderMplayer.h"
#include "ffdebug.h"
#pragma warning(disable:4244)

//============================ TrenderedSubtitleWordBase =============================
TrenderedSubtitleWordBase::~TrenderedSubtitleWordBase()
{
    if (own)
        for (int i=0;i<3;i++) {
            aligned_free(bmp[i]);
            aligned_free(msk[i]);
            aligned_free(outline[i]);
            aligned_free(shadow[i]);
        }
}

//============================== TrenderedSubtitleLine::TprintPrefs ===============================
TprintPrefs::TprintPrefs(IffdshowBase *Ideci,const TfontSettings *IfontSettings) {
     memset(this,0,sizeof(this)); // This doesn't seem to help after optimization.
     dx = dy = 0;
     isOSD=false;
     xpos = ypos = 0;
     align = 0;
     linespacing = 0;
     sizeDx=0;
     sizeDy=0;
     if (IfontSettings)
      fontSettings = *IfontSettings;
     deci=Ideci;
     config=NULL;
     posXpix=0;
     vobchangeposition = false;
     vobscale = vobaamode = vobaagauss = 0;
     fontchangesplit=false;
     fontsplit = 0;
     textBorderLR=0;
     tabsize=8;
     dvd=false;
     shadowMode = shadowSize = csp = 0;
     outlineWidth = 0;
     blur=false;
     outlineBlur=false;
     clipdy=0;
     sar=Rational(1,1);
     opaqueBox=false;
     subformat=-1;
     xinput=0;
     yinput=0;
     rtStart=REFTIME_INVALID;
     yuvcolor=YUVcolorA(fontSettings.color,fontSettings.bodyAlpha);
     outlineYUV=YUVcolorA(fontSettings.outlineColor,fontSettings.outlineAlpha);
     shadowYUV=YUVcolorA(fontSettings.shadowColor,fontSettings.shadowAlpha);
 }

bool TprintPrefs::operator != (const TprintPrefs &rt) const
{
     // compare all members except rtStart
     if (dx == rt.dx && dy == rt.dy && clipdy == rt.clipdy
      && isOSD == rt.isOSD
      && xpos == rt.xpos && ypos == rt.ypos
      && align == rt.align
      && linespacing == rt.linespacing
      && sizeDx == rt.sizeDx && sizeDy == rt.sizeDy
      && posXpix == rt.posXpix
      && vobchangeposition == rt.vobchangeposition && vobscale == rt.vobscale && vobaamode == rt.vobaamode && vobaagauss == rt.vobaagauss
      && fontchangesplit == rt.fontchangesplit && fontsplit == rt.fontsplit
      && textBorderLR == rt.textBorderLR
      && tabsize == rt.tabsize
      && dvd == rt.dvd
      && shadowMode == rt.shadowMode && shadowAlpha == rt.shadowAlpha
      && shadowSize == rt.shadowSize
      && blur == rt.blur && outlineBlur == rt.outlineBlur
      && csp == rt.csp
      && outlineWidth == rt.outlineWidth
      && sar == rt.sar
      && opaqueBox == rt.opaqueBox
      && subformat == rt.subformat
      && xinput == rt.xinput && yinput == rt.yinput
      && fontSettings == rt.fontSettings
      && yuvcolor == rt.yuvcolor && outlineYUV == rt.outlineYUV && shadowYUV == rt.shadowYUV)
        return false;
     else
        return true;
 }

 bool TprintPrefs::operator == (const TprintPrefs &rt) const
 {
     // compare all members except rtStart
     return !(*this != rt);
 }

void TprintPrefs::debug_print() const
{
     DPRINTF(_l("dx %d,dy %d,clipdy %d,isOSD %d,xpos %d,ypos %d,align %d,linespacing %d,sizeDx %d,sizeDy %d,posXpix %d,")
     _l("vobchangeposition %d,vobscale %d,vobaamode %d,vobaagauss %d,")
     _l("fontchangesplit %d,fontsplit %d,textBorderLR %d,tabsize %d,dvd %d,shadowMode %d, shadowAlpha %d,blur %d,outlineBlur %d,")
     _l("csp %d,opaqueBox %d,subformat %d,xinput %d,yinput %d"),
     dx,dy,clipdy,isOSD,xpos,ypos,align,linespacing,sizeDx,sizeDy,posXpix,
     vobchangeposition,vobscale,vobaamode,vobaagauss,
     fontchangesplit,fontsplit,textBorderLR,tabsize,dvd,shadowMode, shadowAlpha,blur,outlineBlur,
     csp,opaqueBox,subformat,xinput,yinput);
}

//============================== TrenderedSubtitleLine ===============================
unsigned int TrenderedSubtitleLine::width(void) const
{
    if (empty())
        return 0;
    unsigned int dx=0;
    foreach (TrenderedSubtitleWordBase *word, *this)
        dx+=word->dxChar;
    return dx;
}

unsigned int TrenderedSubtitleLine::height(void) const
{
    if (empty())
        return 0;
    int aboveBaseline=0,belowBaseline=0;
    foreach (TrenderedSubtitleWordBase *word, *this) {
        aboveBaseline=std::max<int>(aboveBaseline,word->get_baseline());
        belowBaseline=std::max<int>(belowBaseline,word->dy[0]-word->get_baseline());
    }
    return aboveBaseline+belowBaseline;
}

double TrenderedSubtitleLine::charHeight(void) const
{
    if (empty())
        return emptyHeight;
    double aboveBaseline=0,belowBaseline=0;
    foreach (TrenderedSubtitleWordBase *word, *this) {
      aboveBaseline=std::max<int>(aboveBaseline,word->get_ascent());
      belowBaseline=std::max<int>(belowBaseline,word->get_descent());
    }
    return aboveBaseline + belowBaseline;
}

unsigned int TrenderedSubtitleLine::baselineHeight(void) const
{
    if (empty())
        return 0;
    unsigned int aboveBaseline=0;
    foreach (TrenderedSubtitleWordBase *word, *this)
        aboveBaseline=std::max<unsigned int>(aboveBaseline, word->get_baseline());
    return aboveBaseline;
}

int TrenderedSubtitleLine::get_topOverhang(void) const
{
    if (empty())
        return 0;
    int baseline=baselineHeight();
    int topOverhang=0;
    foreach (TrenderedSubtitleWordBase *word, *this)
        topOverhang=std::min(topOverhang, int(baseline - word->get_baseline() - word->getOverhang().top));
    return -topOverhang;
}

int TrenderedSubtitleLine::get_bottomOverhang(void) const
{
    if (empty())
        return 0;
    int baseline=baselineHeight();
    int bottomOverhang=0;
    foreach (TrenderedSubtitleWordBase *word, *this)
        bottomOverhang=std::max(bottomOverhang, int((int)word->dxChar - word->get_baseline() + word->getOverhang().bottom));
    return bottomOverhang+baseline - charHeight();
}

int TrenderedSubtitleLine::get_leftOverhang(void) const
{
    if (empty())
        return 0;
    int dx=0;
    int leftOverhang=0;
    foreach (TrenderedSubtitleWordBase *word, *this) {
        leftOverhang=std::min(leftOverhang, int(dx - word->getOverhang().left));
        dx+=word->dxChar;
    }
    return -leftOverhang;
}

int TrenderedSubtitleLine::get_rightOverhang(void) const
{
    if (empty())
        return 0;
    int dx=0;
    int rightOverhang=0;
    foreach (TrenderedSubtitleWordBase *word, *this) {
        dx += word->dxChar;
        rightOverhang = std::max(rightOverhang, int(dx + word->getOverhang().right));
    }
    return rightOverhang-dx;
}

void TrenderedSubtitleLine::prepareKaraoke(void)
{
    if (!firstrun)
        return;
    firstrun = false;
    int sequenceWidth;
    REFERENCE_TIME karaokeStart = REFTIME_INVALID;
    for (iterator w = begin() ; w != end() ;) {
        if (((TrenderedTextSubtitleWord *)(*w))->props.karaokeNewWord) {
            sequenceWidth = (*w)->dxChar;
            for (iterator s = w + 1 ; s != end() ; s++) {
                if (((TrenderedTextSubtitleWord *)(*s))->props.karaokeNewWord)
                    break;
                else
                    sequenceWidth += (*s)->dxChar;
            }
            if (karaokeStart == REFTIME_INVALID)
                karaokeStart = ((TrenderedTextSubtitleWord *)(*w))->props.karaokeStart;
            for (iterator s = w ; s != end() ; s++) {
                if (((TrenderedTextSubtitleWord *)(*s))->props.karaokeNewWord && s != w)
                    break;
                if (sequenceWidth)
                    ((TrenderedTextSubtitleWord *)(*s))->props.karaokeDuration *= (double)(*s)->dxChar / sequenceWidth;
                ((TrenderedTextSubtitleWord *)(*s))->props.karaokeStart = karaokeStart;
                karaokeStart += ((TrenderedTextSubtitleWord *)(*s))->props.karaokeDuration;
            }
        }
        // Drop empty words here.
        // Empty words had properties which might be necessary for karaoke timing calculation.
        if ((*w)->dxChar == 0 && (*w)->dyChar == 0) {
            delete *w;
            w = erase(w);
        } else {
            w++;
        }
    }
}

void TrenderedSubtitleLine::print(
    int startx,int starty,
    const TprintPrefs &prefs,
    unsigned int prefsdx,
    unsigned int prefsdy,
    unsigned char **dst,
    const stride_t *stride)
{
    orderedPoint.y = printedRect.top = starty;
    orderedPoint.x = printedRect.left = startx;

    int baseline=baselineHeight();
    const TcspInfo *cspInfo = csp_getInfo(prefs.csp);
    for (const_iterator w=begin();w!=end() && startx<(int)prefsdx;startx+=(*w)->dxChar,w++) {
        TrenderedSubtitleWordBase *word = *w;
        startx += word->getPathOffsetX();
        const unsigned char *msk[3],*bmp[3];
        unsigned char *dstLn[3];
        int x[3];
        unsigned int dx[3];
        int dy[3];
        for (int i=0;i<3;i++) {
            x[i]=startx>>cspInfo->shiftX[i];
            msk[i]=word->msk[i];
            bmp[i]=word->bmp[i];
            if (prefs.align!=ALIGN_FFDSHOW && x[i]<0) {
                msk[i]+=-x[i];
                bmp[i]+=-x[i];
            }
            int sy=(starty + baseline - word->get_baseline() + word->getPathOffsetY()) >> cspInfo->shiftY[i];
            dy[i]=std::min((int(prefsdy)>>cspInfo->shiftY[i])-sy,int(word->dy[i]));
            dstLn[i]=dst[i] + int(sy * stride[i]);
            if (x[i]>0)
                dstLn[i]+=x[i]*cspInfo->Bpp;

            if (x[i]+word->dx[i]>(prefsdx>>cspInfo->shiftX[i]))
                dx[i]=(prefsdx>>cspInfo->shiftX[i])-x[i];
            else if (x[i]<0)
                dx[i]=word->dx[i]+x[i];
            else
                dx[i]=word->dx[i];
            dx[i]=std::min(dx[i],prefsdx>>cspInfo->shiftX[i]);
        }
        printedRect.top = std::min<long>(printedRect.top, starty);
        printedRect.left = std::min<long>(printedRect.left, startx);
        printedRect.bottom = std::max<long>(printedRect.bottom, starty + dy[0]);
        printedRect.right = std::max<long>(printedRect.right, startx + dx[0]);

        word->print(startx, starty,dx,dy,dstLn,stride,bmp,msk,prefs.rtStart);
    }
}

const TSubtitleProps& TrenderedSubtitleLine::getProps() const
{
    // Which props should represent this line?
    // The first word that have dxChar should to make sense.
    // If there is none, return this->props.
    // Caller must be sure it is dealing with text subtitles.
    foreach (TrenderedSubtitleWordBase *word0, *this) {
        TrenderedTextSubtitleWord *word = (TrenderedTextSubtitleWord *)word0;
        if (word->dxChar) return word->props;
    }
    return props;
}

void TrenderedSubtitleLine::clear(void)
{
    foreach (TrenderedSubtitleWordBase *word, *this)
       delete word;
    std::vector<value_type>::clear();
}

size_t TrenderedSubtitleLine::getMemorySize() const
{
    size_t memSize = 0;
    foreach (const TrenderedSubtitleWordBase *word, *this)
        memSize += word->getMemorySize();
    return memSize;
}

//============================== TrenderedSubtitleLines ==============================
void TrenderedSubtitleLines::print(
    const TprintPrefs &prefs,
    unsigned char **dst,
    const stride_t *stride)
{
    // Use the same renderer for SSA and SRT if extended tags option is checked (both formats can hold SSA tags and HTML tags)
    if ((prefs.subformat & Tsubreader::SUB_FORMATMASK) == Tsubreader::SUB_SSA
        || ((prefs.subformat & Tsubreader::SUB_FORMATMASK) == Tsubreader::SUB_SUBVIEWER) 
        && prefs.deci->getParam2(IDFF_subExtendedTags))
        return printASS(prefs,dst,stride);
    double y=0;
    if (empty()) return;
    unsigned int prefsdx,prefsdy;
    if (prefs.sizeDx && prefs.sizeDy) {
        prefsdx=prefs.sizeDx;
        prefsdy=prefs.sizeDy;
    } else {
        prefsdx=prefs.dx;
        prefsdy=prefs.dy;
    }

    double h=0,h1=0;
    for (const_iterator i=begin();i!=end();i++) {
        double h2=h1+(*i)->height();
        h1+=(double)prefs.linespacing*(*i)->charHeight()/100;
        if (h2>h)
            h=h2;
    }
    
    if (prefs.isOSD && prefs.ypos>=0)        // IffdshowDecVideo::drawOSD
        y = (double)(prefs.ypos*prefsdy)/100.0;
    else if (prefs.ypos<0)                   // prefs.ypos<0 means -prefs.ypos is absolute potision. OSD use this.
        y = -(double)prefs.ypos;
    else
        y = ((double)prefs.ypos*prefsdy)/100.0-h/2;

    if (prefs.ypos>=0 && y+h >= (double)prefsdy)
        y=(double)prefsdy-h-1;

    for (const_iterator i=begin();i!=end();y+=(double)prefs.linespacing*(*i)->charHeight()/100,i++) {
        if (y<0) continue;

        if ((unsigned int)y>=prefsdy) break;
        int x;
        unsigned int cdx=(*i)->width();
        if (prefs.xpos<0)
            x=-prefs.xpos; // OSD
        else {
            // subtitles
            x=(prefs.xpos * prefsdx)/100 + prefs.posXpix;
            switch (prefs.align) {
                case ALIGN_FFDSHOW:x=x-cdx/2;if (x<0) x=0;if (x+cdx>=prefsdx) x=prefsdx-cdx;break;
                case ALIGN_LEFT:break;
                case ALIGN_CENTER:x=x-cdx/2;break;
                case ALIGN_RIGHT:x=x-cdx;break;
            }
        }
        if (x+cdx>=prefsdx && !prefs.isOSD) x=prefsdx-cdx-1;
        if (x<0) x=0;
        (*i)->print(x,y,prefs,prefsdx,prefsdy,dst,stride); // print a line (=print words).
    }
}

void TrenderedSubtitleLines::printASS(
    const TprintPrefs &prefs,
    unsigned char **dst,
    const stride_t *stride)
{
    double y=0;
    if (empty()) return;
    unsigned int prefsdx,prefsdy;
    if (prefs.sizeDx && prefs.sizeDy) {
        prefsdx=prefs.sizeDx;
        prefsdy=prefs.sizeDy;
    } else {
        prefsdx=prefs.dx;
        prefsdy=prefs.dy;
    }

    std::map<ParagraphKey,ParagraphValue> paragraphs;
    


    // pass 1: prepare paragraphs : a paragraph is a set of lines that have the same properties
    // (same margins, alignment and position)
    foreach (TrenderedSubtitleLine *line, *this) {
        line->prepareKaraoke();
        ParagraphKey pkey(line, prefsdx, prefsdy);
        std::map<ParagraphKey,ParagraphValue>::iterator pi=paragraphs.find(pkey);
        if (pi != paragraphs.end()) {
            pi->second.topOverhang = std::min(pi->second.topOverhang ,double(pi->second.height-line->get_topOverhang()));
            pi->second.bottomOverhang = std::max(pi->second.bottomOverhang ,double(line->get_bottomOverhang()));
            pi->second.height+=line->charHeight();
        } else {
            ParagraphValue pval;
            pval.topOverhang = -line->get_topOverhang();
            pval.bottomOverhang = line->get_bottomOverhang();
            pval.height = line->charHeight();
            paragraphs.insert(std::pair<ParagraphKey,ParagraphValue>(pkey,pval));
        }
    }

    std::sort(begin(),end(),TlayerSort());

    // pass 2: print
    foreach (TrenderedSubtitleLine *line, *this) {
        const TSubtitleProps &lineprops = line->getProps();
        int x=0;
        ParagraphKey pkey(line, prefsdx, prefsdy);
        if (!line->getHasPrintedRect() || lineprops.isMove) {
            std::map<ParagraphKey,ParagraphValue>::iterator pi=paragraphs.find(pkey);
            if (pi != paragraphs.end()) {
                ParagraphValue &pval=pi->second;
                if (pval.firstuse) {
                    pval.firstuse=false;
                    switch (pkey.alignment) {
                    case 9: // SSA mid
                    case 10:
                    case 11:
                        // With middle alignment and position/move tag we position the paragraph to the requested
                        // position basing on the anchor point set at the middle
                        if (pkey.isPos || pkey.isMove)
                            pval.y=pkey.marginTop-pval.height/2.0;
                        else // otherwise put the paragraph on the center of the screen (vertical margin is ignored)
                            pval.y=(prefsdy - pval.height)/2.0;
                        break;
                    case 5: // SSA top
                    case 6:
                    case 7:
                        pval.y = pkey.marginTop + pval.topOverhang;
                        break;
                    case 1: // SSA bottom
                    case 2:
                    case 3:
                    default:
                        // If the text is supposed to be placed at the bottom of the screen 
                        // or has no vertical alignment defined
                        // then apply the vertical position setting
                        if (pkey.marginBottom == 0 && (prefs.deci->getParam2(IDFF_subSSAOverridePlacement)
                             || (prefs.subformat & Tsubreader::SUB_FORMATMASK) == Tsubreader::SUB_SUBVIEWER))
                            pval.y=((double)prefs.ypos*prefsdy)/100.0-pval.height + pval.topOverhang;
                        else
                            pval.y=(double)prefsdy-pval.height - pkey.marginBottom + pval.topOverhang;
                     break;
                    }

                    // If option is checked (or if subs are SUBVIEWER), correct vertical placement if text goes out of the screen
                    if ((prefs.deci->getParam2(IDFF_subSSAMaintainInside) 
                        || (prefs.subformat & Tsubreader::SUB_FORMATMASK) == Tsubreader::SUB_SUBVIEWER) && !lineprops.isMove) {
                        if (pval.y+pval.height>prefsdy)
                            pval.y=prefsdy-pval.height;
                        if (pval.y<0)
                            pval.y=0;
                    }


                    // Moving (scrolling text) : scroll from t1 to t2. Calculate vertical position
                    if (lineprops.isMove && prefs.rtStart >= lineprops.get_moveStart()) {
                        // Stop scrolling if beyond t2
                        if (prefs.rtStart >= lineprops.get_moveStop())
                            pval.y += lineprops.get_movedistanceV(prefsdy);
                        else
                            pval.y += lineprops.get_movedistanceV(prefsdy)*
                                      (prefs.rtStart-lineprops.get_moveStart())/(lineprops.get_moveStop()-lineprops.get_moveStart());
                    }
                }
                y=pval.y;
                pval.y += line->charHeight();
            }

            if (y>=(double)prefsdy) break;
            unsigned int cdx=line->width();
            // Left and right margins need to be recalculated according to the length of the line
            int marginL=lineprops.get_marginL(prefsdx, cdx);
            int marginR=lineprops.get_marginR(prefsdx, cdx);
            int leftOverhang=line->get_leftOverhang();
            
            switch (lineprops.alignment) {
            case 1: // left(SSA)
            case 5:
            case 9:
                x=marginL - leftOverhang;
                break;
            case 3: // right(SSA)
            case 7:
            case 11:
                x=prefsdx - cdx - marginR - leftOverhang;
                break;
            case 2: // center(SSA)
            case 6:
            case 10:
            default:
                // If the text is supposed to be placed at the center of the screen 
                // or has no horizontal alignment defined
                // then apply the horizontal position setting
                if (marginL==0 && (prefs.deci->getParam2(IDFF_subSSAOverridePlacement)
                     || (prefs.subformat & Tsubreader::SUB_FORMATMASK) == Tsubreader::SUB_SUBVIEWER))
                    x = ((double)prefs.xpos * prefsdx)/100.0 - (int)(cdx+marginR)/2 - leftOverhang;
                else if (lineprops.isPos) // If position defined, then marginL is relative to left border of the screen
                    x = marginL-leftOverhang;
                else // else marginL is relative to the center of the screen
                    x = ((int)prefsdx - marginL - marginR - (int)cdx)/2 + marginL - leftOverhang;
                break;
            }

            // If option is checked (or if subs are SUBVIEWER), correct horizontal placement if text goes out of the screen
            if ((prefs.deci->getParam2(IDFF_subSSAMaintainInside) 
              || (prefs.subformat & Tsubreader::SUB_FORMATMASK) == Tsubreader::SUB_SUBVIEWER) && !lineprops.isMove) {
                if (x+cdx>prefsdx)
                    x=prefsdx-cdx;
                if (x < 0)
                    x=0;
            }

            if (!lineprops.isMove) {
                int lineHight = (int)line->charHeight();
                CRect myrect(x, y, x + cdx, y + lineHight);
                CRect hisrect;
                bool again = false;
                for (const_iterator l = begin(); l != end() || again ; l++) {
                    if (again) {
                        l = begin();
                        // We can skip check if (l == end()) break; safely as this is guaranteed to be not empty.
                        again = false;
                    }
                    ParagraphKey hiskey(*l, prefsdx, prefsdy);
                    if (pkey != hiskey && (*l)->checkCollision(myrect, hisrect)) {
                        if (lineprops.alignment <= 3) {
                            // bottom
                            y = hisrect.top - lineHight - 1;
                            myrect = CRect(x, y, x + cdx, y + lineHight);
                            if (lineHight > 0)
                                again = true;
                        } else {
                            // Top, middle
                            y = hisrect.bottom + 1;
                            myrect = CRect(x, y, x + cdx, y + lineHight);
                            again = true;
                        }
                    }
                }
            }
        } else {
            x = line->getOrderedPoint().x;
            y = line->getOrderedPoint().y;
        }
          
        // Moving (scrolling text) : scroll from t1 to t2. Calculate horizontal position
        if (lineprops.isMove && prefs.rtStart >= lineprops.get_moveStart()) {
            // Stop scrolling if beyond t2
            if (prefs.rtStart >= lineprops.get_moveStop())
                x += lineprops.get_movedistanceH(prefsdx);
            else
                x += lineprops.get_movedistanceH(prefsdx)*
                     (prefs.rtStart-lineprops.get_moveStart())/(lineprops.get_moveStop()-lineprops.get_moveStart());
        }

       line->print(x,y,prefs,prefsdx,prefsdy,dst,stride);
    }

    foreach (TrenderedSubtitleLine *line, *this) {
        if (!line->getProps().isMove)
            line->setPrinted();
    }
}

TrenderedSubtitleLines::ParagraphKey::ParagraphKey(TrenderedSubtitleLine *line, unsigned int prefsdx, unsigned int prefsdy):
    posx(INT_MIN),
    posy(INT_MIN)
{
    const TSubtitleProps &lineprops = line->getProps();
    alignment = lineprops.alignment;
    marginBottom = lineprops.get_marginBottom(prefsdy);
    marginTop = lineprops.get_marginTop(prefsdy);
    marginL = lineprops.get_marginL(prefsdx);
    marginR = lineprops.get_marginR(prefsdx);
    isPos = lineprops.isPos;
    isMove = lineprops.isMove;
    hasPrintedRect = line->getHasPrintedRect();

    layer = lineprops.layer;
    if (isPos || isMove) {
        posx = lineprops.posx;
        posy = lineprops.posy;
    }
    if (!isMove)
        printedRect = line->getPrintedRect();
};

void TrenderedSubtitleLines::clear(void)
{
    foreach (TrenderedSubtitleLine *line, *this) {
        line->clear();
        delete line;
    }
    reset();
}

size_t TrenderedSubtitleLines::getMemorySize() const
{
    size_t memSize = 0;
    foreach (const TrenderedSubtitleLine *line, *this)
        memSize += line->getMemorySize();
    return memSize;
}

bool TrenderedSubtitleLines::ParagraphKey::operator < (const ParagraphKey &rt) const
{
    if (alignment<rt.alignment) return true;
    if (alignment>rt.alignment) return false;
    if (marginTop<rt.marginTop) return true;
    if (marginTop>rt.marginTop) return false;
    if (marginBottom<rt.marginBottom) return true;
    if (marginBottom>rt.marginBottom) return false;
    if (marginL<rt.marginL) return true;
    if (marginL>rt.marginL) return false;
    if (marginR<rt.marginR) return true;
    if (marginR>rt.marginR) return false;
    if (isPos<rt.isPos) return true;
    if (isPos>rt.isPos) return false;
    if (posx<rt.posx) return true;
    if (posx>rt.posx) return false;
    if (posy<rt.posy) return true;
    if (posy>rt.posy) return false;
    if (layer<rt.layer) return true;
    if (layer>rt.layer) return false;
    if (hasPrintedRect<rt.hasPrintedRect) return true;
    if (hasPrintedRect>rt.hasPrintedRect) return false;
    if (printedRect<rt.printedRect) return true;
    if (printedRect>rt.printedRect) return false;
    return false;
}

bool TrenderedSubtitleLines::ParagraphKey::operator != (const ParagraphKey &rt) const
{
    // compare except printedRect
    if (alignment == rt.alignment
      && marginTop == rt.marginTop
      && marginBottom == rt.marginBottom
      && marginL == rt.marginL
      && marginR == rt.marginR
      && isPos == rt.isPos
      && posx == rt.posx
      && posy == rt.posy
      && layer == rt.layer
      && hasPrintedRect == rt.hasPrintedRect)
        return false;
    else
        return true;
}

bool TrenderedSubtitleLines::ParagraphKey::operator == (const ParagraphKey &rt) const
{
    return !(*this != rt);
}

bool TrenderedSubtitleLines::TlayerSort::operator() (TrenderedSubtitleLine *lt, TrenderedSubtitleLine *rt) const
{
    return lt->getProps().layer < rt->getProps().layer;
}

//============================== TrenderedVobsubWord ===============================
void TrenderedVobsubWord::print(int startx, int starty /* not used */, unsigned int sdx[3],int sdy[3],unsigned char *dstLn[3],const stride_t stride[3],const unsigned char *bmp[3],const unsigned char *msk[3],REFERENCE_TIME rtStart) const
{
    if (sdy[0]<=0 || sdy[1]<0)
        return;
    int sdx15=sdx[0]-15;
    for (unsigned int y=0;y<(unsigned int)sdy[0];y++,dstLn[0]+=stride[0],msk[0]+=bmpmskstride[0],bmp[0]+=bmpmskstride[0]) {
        int x=0;
        for (;x<sdx15;x+=16) {
            __m64 mm0=*(__m64*)(dstLn[0]+x),mm1=*(__m64*)(dstLn[0]+x+8);
            mm0=_mm_subs_pu8(mm0,*(__m64*)(msk[0]+x));mm1=_mm_subs_pu8(mm1,*(__m64*)(msk[0]+x+8));
            mm0=_mm_adds_pu8(mm0,*(__m64*)(bmp[0]+x));mm1=_mm_adds_pu8(mm1,*(__m64*)(bmp[0]+x+8));
            *(__m64*)(dstLn[0]+x)=mm0;*(__m64*)(dstLn[0]+x+8)=mm1;
        }
        for (;x<int(sdx[0]);x++) {
            int c=dstLn[0][x];
            c-=msk[0][x];if (c<0) c=0;
            c+=bmp[0][x];if (c>255) c=255;
            dstLn[0][x]=(unsigned char)c;
        }
    }
    __m64 m128=_mm_set1_pi8((char)-128/* 0x80 */),m0=_mm_setzero_si64(),mAdd=shiftChroma?m128:m0;
    int add=shiftChroma?128:0;
    int sdx7=sdx[1]-7;
    for (unsigned int y=0;y<dy[1];y++,dstLn[1]+=stride[1],dstLn[2]+=stride[2],msk[1]+=bmpmskstride[1],bmp[1]+=bmpmskstride[1],bmp[2]+=bmpmskstride[2]) {
        int x=0;
        for (;x<sdx7;x+=8) {
            __m64 mm0=*(__m64*)(dstLn[1]+x);
            __m64 mm1=*(__m64*)(dstLn[2]+x);

            psubb(mm0,m128);
            psubb(mm1,m128);

            const __m64 msk8=*(const __m64*)(msk[1]+x);

            __m64 mskU=_mm_cmpgt_pi8(m0,mm0); //what to be negated
            mm0=_mm_or_si64(_mm_and_si64(mskU,_mm_adds_pu8(mm0,msk8)),_mm_andnot_si64(mskU,_mm_subs_pu8(mm0,msk8)));

            __m64 mskV=_mm_cmpgt_pi8(m0,mm1);
            mm1=_mm_or_si64(_mm_and_si64(mskV,_mm_adds_pu8(mm1,msk8)),_mm_andnot_si64(mskV,_mm_subs_pu8(mm1,msk8)));

            mm0=_mm_add_pi8(_mm_add_pi8(mm0,*(__m64*)(bmp[1]+x)),mAdd);
            mm1=_mm_add_pi8(_mm_add_pi8(mm1,*(__m64*)(bmp[2]+x)),mAdd);

            *(__m64*)(dstLn[1]+x)=mm0;
            *(__m64*)(dstLn[2]+x)=mm1;
        }
        for (;x<int(sdx[1]);x++) {
            int m=msk[1][x],c;
            c=dstLn[1][x];
            c-=128;
            if (c<0) {c+=m;if (c>0) c=0;}
            else     {c-=m;if (c<0) c=0;}
            c+=bmp[1][x];
            c+=add;
            dstLn[1][x]=c;//(unsigned char)limit(c,0,255);

            c=dstLn[2][x];
            c-=128;
            if (c<0) {c+=m;if (c>0) c=0;}
            else     {c-=m;if (c<0) c=0;};
            c+=bmp[2][x];
            c+=add;
            dstLn[2][x]=c;//(unsigned char)limit(c,0,255);
        }
    }
    _mm_empty();
}

//==================================== Tfont ====================================
Tfont::Tfont(IffdshowBase *Ideci):
    fontManager(NULL),
    deci(Ideci),
    hdc(NULL),
    oldFont(NULL),
    height(0)
{
    init();
}
Tfont::~Tfont()
{
    done();
}
void Tfont::init()
{
    done();
    hdc=CreateCompatibleDC(NULL);
    if (!hdc) return;
    SetBkMode(hdc,TRANSPARENT); 
    SetTextColor(hdc,0xffffff); 
    SetMapMode(hdc,MM_TEXT);
}
void Tfont::done(void)
{
    if (hdc) {
        if (oldFont) SelectObject(hdc,oldFont);
        oldFont = NULL;
        DeleteDC(hdc);
        hdc = NULL;
    }
}

void Tfont::prepareC(TsubtitleText *sub,const TprintPrefs &prefs,bool forceChange)
{
    sub->prepareGlyph(prefs,*this,forceChange);
    lines.insert(lines.end(),sub->lines.begin(),sub->lines.end());
}

int Tfont::print(
    TsubtitleText *sub,
    bool forceChange,
    const TprintPrefs &prefs,
    unsigned char **dst,
    const stride_t *stride)
{
    if (!sub) return 0;
    prepareC(sub,prefs,forceChange);
    lines.print(prefs,dst,stride);
    int h = 0;
    foreach (TrenderedSubtitleLine *line, lines)
        h += line->height();
    reset();
    return h;
}

void Tfont::print(
    const TprintPrefs &prefs,
    unsigned char **dst,
    const stride_t *stride)
{
    lines.print(prefs,dst,stride);
}
