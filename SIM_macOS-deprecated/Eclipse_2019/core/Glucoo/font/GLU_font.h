#ifndef _GLU_FONT_H
#define _GLU_FONT_H


#include "RH_common.h"
#include "RH_config.h"
#include "GLU_pixel.h"


#ifdef __cpluplus
extern "C"{
#endif


#if   ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_EXTERN_TTF )

#elif ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_LOCAL_ARRAY )

#elif ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_LOCAL_BITMAP )

#else

  #error "Unknown font data source."
#endif


struct rhtt_fontinfo{
    uint8_t   h;
    uint8_t   w;
    char      c;
    uint8_t   *data;
};
typedef struct rhtt_fontinfo rhtt_fontinfo;



typedef enum{
    kGLU_Font_Unscii            ,
    kGLU_Font_ArialRounded_Bold ,
    kGLU_Font_CourierNew        ,
    kGLU_Font_CourierNew_Italic ,
    kGLU_Font_CourierNew_Bold   ,
    kGLU_Font_NewYork           ,
    kGLU_Font_NewYork_Italic    ,
    kGLU_Font_Optima            ,
    kGLU_Font_SignPrinter       ,
    kGLU_NUM_FontStyle
}GLU_ENUM(Font);

typedef enum{
    kGLU_Align_Right   ,
    kGLU_Align_Left    ,
    kGLU_Align_Middle  ,
    kGLU_Align_Justify
}GLU_ENUM(Align);

struct GLU_SRCT(Text){
    GLU_ENUM(Font)  font;
    uint16_t         size;
    GLU_TYPE(Color) color;
    GLU_ENUM(Align) align;
    const char*     str;
};
typedef struct GLU_SRCT(Text) GLU_SRCT(Text);

struct GLU_SRCT(FontImg){
    uint8_t* img_buf;
    var      img_h;
    var      img_w;
};
typedef struct GLU_SRCT(FontImg) GLU_SRCT(FontImg);

void                RH_PREMAIN            GLU_FUNC( Font, init           ) ( void );
           
void                                      GLU_FUNC( Font, set_font       ) ( GLU_ENUM(Font) font   );
void                                      GLU_FUNC( Font, set_size       ) ( uint16_t       size   );
           
uint8_t                                   GLU_FUNC( Font, get_size       ) ( void );
GLU_ENUM(Font)                            GLU_FUNC( Font, get_font       ) ( void );
           
void                                      GLU_FUNC( Font, backupCache    ) ( void );
void                                      GLU_FUNC( Font, restoreCache   ) ( void );

GLU_SRCT(FontImg)*  RH_RESULT RH_NULLABLE GLU_FUNC( Font, out_chr_Img    ) ( uint16_t    chr );
GLU_SRCT(FontImg)*  RH_RESULT RH_NULLABLE GLU_FUNC( Font, out_str_Img    ) ( const char* str );
GLU_SRCT(FontImg)*  RH_RESULT RH_NULLABLE GLU_FUNC( Font, out_txt_Img    ) ( const char* str, size_t width, GLU_ENUM(Align) align );

void                                      GLU_FUNC( Font, get_chr_ImgInfo) ( var RH_NULLABLE *width, var RH_NULLABLE *height, char        c   );
void                                      GLU_FUNC( Font, get_str_ImgInfo) ( var RH_NULLABLE *width, var RH_NULLABLE *height, const char* str );
           
int                                       GLU_FUNC( Font, get_str_WordCnt) ( var width, const char* str );



#ifdef __cpluplus
}
#endif


#endif
