

//#include "RH_gui_config.h"
#include "RH_gui.h"
#include "RH_data.h"
#include "RH_lib.h"
#include "RH_graphic.h"
#include "RH_gui_font.h"

void __attribute__((weak)) GUI_DrawArea       (int x1,int y1,int x2,int y2,const __Pixel_t* pixData){
// THIS MAY COST SOME TIME.
}
void (*GUI_API_DrawArea)                      (int x1,int y1,int x2,int y2,const __Pixel_t* pixData) = GUI_DrawArea;

void __attribute__((weak)) GUI_DummyDrawPixel (int x,int y,const __Pixel_t pixData){
// IF U DONT GIVE ME A PEN, HOW CAN I DRAW !?
}
void (*GUI_API_DrawPixel)                     (int x ,int y ,const __Pixel_t pixData)          = GUI_DummyDrawPixel;

void __attribute__((weak)) GUI_AsserParam     (bool expression,const char* WHAT_IS_WRONG){
// DONT KEEP MY MOTH SHUT, I GOT A PROBLEM TO REPORT.
}
void (*GUI_API_AssertParam)                   (bool expression,const char* WHAT_IS_WRONG)      = GUI_AsserParam;

void __attribute__((weak)) GUI_Delay          (unsigned long ms){
    ms*=1000;
    while(ms--){}
}
void (*GUI_API_DelayMs)                       (unsigned long ms)                               = GUI_Delay;

#define M_SCREEN_MAIN   0
#define M_SCREEN_CNT    3




#if GUI_WINDOW_DISPLAY
struct __GUI_INT_Window_t{
    struct __GUI_Window_t config;
    void (*insert_func)(__GUI_Window_t*);
    void (*remove_func)(__GUI_Window_t*);
};
typedef struct __GUI_INT_Window_t __GUI_INT_Window_t;
#endif

typedef __Stack_t      __LINK_AreaRefreash;
typedef __LinkLoopNode __LINK_WindowCFG;

static struct{
    __PixelUnit_t GRAM[M_SCREEN_CNT][ GUI_Y_WIDTH][ GUI_X_WIDTH ];
    size_t           allocated_byte;

    bool             autoDisplay;

    __LINK_AreaRefreash*     areaNeedRefreashHead;
    size_t                   areaNeedRefreashCnt;
    size_t                   areaNeedRefreashPixelCnt;
    
#if GUI_WINDOW_DISPLAY
    __LINK_WindowCFG*        windowCFG;
#endif
}Screen;

static void __attribute__((constructor)) GUI_Init(void){
    memset( Screen.GRAM , 0, M_SCREEN_CNT*GUI_Y_WIDTH*GUI_X_WIDTH*sizeof(__Pixel_t) );
    
    Screen.autoDisplay = false;
    
    Screen.allocated_byte = 0;
    __Stack_createBase( &Screen.areaNeedRefreashHead );
    Screen.areaNeedRefreashCnt      = 0;
    Screen.areaNeedRefreashPixelCnt = 0;
    
    Screen.windowCFG = NULL;
}

void GUI_RefreashScreenArea( int xs,int ys,int xe,int ye ){
    printf("[%d,%d] -> [%d,%d]\n",xs,ys,xe,ye);
    int x_width = xe-xs+1;
    int y_width = ye-ys+1;
    if(GUI_API_DrawArea != NULL){
        __Pixel_t* p = (__Pixel_t*)__malloc((x_width)*(y_width)*sizeof(__Pixel_t));
        (*GUI_API_DrawArea)( xs , ys , xe , ye ,
                            __memgrab_Area(p, Screen.GRAM[M_SCREEN_MAIN][0] ,\
                                              sizeof(__Pixel_t)             ,\
                                              GUI_X_WIDTH                   ,\
                                              xs, ys, xe, ye                ) );
        __free(p);
    }
    else{
        for(int y=ys;y<=ye;y++)
            for(int x=xs;x<=xe;x++)
                (*GUI_API_DrawPixel)(x,y,Screen.GRAM[M_SCREEN_MAIN][y][x].data);
    }
}

void GUI_RefreashScreen(void){
    __exit( Screen.areaNeedRefreashHead == NULL );
    __Area_t *p = NULL;
    if( Screen.areaNeedRefreashPixelCnt >= GUI_X_WIDTH*GUI_Y_WIDTH ){
        GUI_RefreashScreenArea( 0, 0, GUI_X_WIDTH-1, GUI_Y_WIDTH-1 );
        while( kStatus_Empty != __Stack_empty(&Screen.areaNeedRefreashHead) ){
            __Stack_pop( &Screen.areaNeedRefreashHead, (void**)&p );
            __free(p);
        }
    }else{
        while( kStatus_Empty != __Stack_empty(&Screen.areaNeedRefreashHead) ){
            __Stack_pop( &Screen.areaNeedRefreashHead, (void**)&p );
            GUI_RefreashScreenArea( (int)(p->xs)             ,\
                                    (int)(p->ys)             ,\
                                    (int)(p->xs+p->width-1)  ,\
                                    (int)(p->ys+p->height-1) );
            __free(p);
        }
    }
    Screen.areaNeedRefreashPixelCnt = 0;
}

void GUI_AddScreenArea( int xs,int ys,int xe,int ye ){
    if( Screen.areaNeedRefreashPixelCnt >= GUI_X_WIDTH*GUI_Y_WIDTH ){
        __Area_t *p = NULL;
        while( kStatus_Empty != __Stack_empty(&Screen.areaNeedRefreashHead) ){
            __Stack_pop( &Screen.areaNeedRefreashHead, (void**)&p );
            __free(p);
        }
        return;
    }
    
    __Area_t* pArea = (__Area_t*)__malloc( sizeof(__Area_t) );
    pArea->xs      = xs;
    pArea->ys      = ys;
    pArea->width   = xe-xs+1;
    pArea->height  = ye-ys+1;
    Screen.areaNeedRefreashPixelCnt += pArea->width*pArea->height;
    __Stack_push( &Screen.areaNeedRefreashHead, (void*)pArea );
}

void GUI_rect_raw( int xs,int ys,int xe,int ye ){
    __GraphInfo_t info = {
        .height = GUI_Y_WIDTH ,
        .width  = GUI_X_WIDTH ,
        .pBuffer = Screen.GRAM[M_SCREEN_MAIN][0]
    };
    
    __Graph_rect_raw(xs,ys,ys,ye,&info,kApplyPixel_fill);
    
    if( Screen.autoDisplay ){
        
    }else{
        GUI_AddScreenArea(xs, ys, xe, ye);
    }
}

#if GUI_WINDOW_DISPLAY

static void __gui_insert_window_MacOS(__GUI_Window_t* config){
    printf("##\n");
    int xs = config->area.xs;
    int ys = config->area.ys;
    int xe = (int)(xs + config->area.width -1);
    int ye = (int)(ys + config->area.height-1);
    __Pixel_t penColor = __Graph_get_penColor();
    size_t    penSize  = __Graph_get_penSize();
    
    
    __GraphInfo_t info = {
        .pBuffer = Screen.GRAM[M_SCREEN_MAIN][0]  ,
        .height  = GUI_Y_WIDTH                    ,
        .width   = GUI_X_WIDTH                    ,
    };
    const int bar_size   = __limit( (int)(config->size), 20, 256 );//38
    const int bar_size_2 = bar_size>>1;
    const int bar_size_4 = bar_size>>2;
    const int bar_rad    = __limit( (int)(config->size), 20, 256 )/5;
    
    // Window Bar
    __Graph_set_penColor(M_COLOR_SILVER);
    __Graph_set_penSize(bar_rad);
    __Graph_rect_round   (xs   , ys         , xe  , ys+bar_size+bar_rad, &info, kApplyPixel_fill);
    
    __Graph_line_raw     (xs   , ye         , xe  , ye                 , &info, kApplyPixel_fill);
    __Graph_line_raw     (xs   , ye-1       , xe  , ye-1               , &info, kApplyPixel_fill);
    
    __Graph_line_raw     (xs   , ys+bar_size, xs  , ye  , &info, kApplyPixel_fill);
    __Graph_line_raw     (xs+1 , ys+bar_size, xs+1, ye  , &info, kApplyPixel_fill);
    __Graph_line_raw     (xe   , ys+bar_size, xe  , ye  , &info, kApplyPixel_fill);
    __Graph_line_raw     (xe-1 , ys+bar_size, xe-1, ye  , &info, kApplyPixel_fill);
    
    // Title
    
    
    // Context
    __Graph_set_penColor(M_COLOR_WHITE);
    __Graph_rect_fill    (xs+2 , ys+bar_size, xe-2, ye-2, &info, kApplyPixel_fill);
    
    // Button
    __Graph_set_penColor(M_COLOR_BLOODYMEAT);
    __Graph_circle_fill  (xs+bar_size_2, __mid(ys,ys+bar_size), bar_size_2 , &info, kApplyPixel_fill);
    
    __Graph_set_penColor(M_COLOR_GOLDEN);
    __Graph_circle_fill  (xs+bar_size+bar_size_4, __mid(ys,ys+bar_size), bar_size_2 , &info, kApplyPixel_fill);
    
    __Graph_set_penColor(M_COLOR_LAWNGREEN);
    __Graph_circle_fill  (xs+(bar_size<<1), __mid(ys,ys+bar_size), bar_size_2 , &info, kApplyPixel_fill);
    
    __Graph_set_penColor(penColor);
    __Graph_set_penSize(penSize);
}

static void __gui_remove_window_MacOS(__GUI_Window_t* config){
    
}

ID_t __attribute__ ((warn_unused_result)) GUI_create_window( __GUI_Window_t* config ){
    __GUI_INT_Window_t* tmp = (__GUI_INT_Window_t*)__malloc( sizeof(__GUI_INT_Window_t) );
    
    tmp->config = *config;

    switch( tmp->config.type ){
        case kGUI_WindowType_macOS:
            tmp->insert_func = __gui_insert_window_MacOS;
            tmp->remove_func = __gui_remove_window_MacOS;
            break;
        default:
            while(1);
    }
    if( Screen.windowCFG==NULL )
        __LINK_Loop_createHead( &Screen.windowCFG , tmp );
    else
        __LINK_Loop_add(&Screen.windowCFG, tmp);
    return (ID_t)tmp;
}

E_Status_t GUI_show_window( ID_t ID ){
    E_Status_t state = __LINK_Loop_find( &Screen.windowCFG, (void*)ID );
    __exitReturn( state != kStatus_Success, state );
    
    (*((__GUI_INT_Window_t*)ID)->insert_func)( &((__GUI_INT_Window_t*)ID)->config );
    if( Screen.autoDisplay ){
        
    }else{
        GUI_AddScreenArea(((__GUI_INT_Window_t*)ID)->config.area.xs ,\
                          ((__GUI_INT_Window_t*)ID)->config.area.ys ,\
                          (int)(((__GUI_INT_Window_t*)ID)->config.area.xs + ((__GUI_INT_Window_t*)ID)->config.area.width -1),\
                          (int)(((__GUI_INT_Window_t*)ID)->config.area.ys + ((__GUI_INT_Window_t*)ID)->config.area.height-1));
    }
    return kStatus_Success;
}

E_Status_t GUI_delete_window( ID_t ID ){
    E_Status_t state = __LINK_Loop_remove( &Screen.windowCFG, (void*)ID );
    __exitReturn( state != kStatus_Success, state );
    
    __free((void*)ID);
    return kStatus_Success;
}



#endif

