#include "GLU_glucoo.h"
#include "BLK_data.h"
#include "BLK_graphic.h"

#if ( RH_CFG_SCREEN_HEIGHT < 16 )
  #warning "Screen height may be too small."
#endif

#if ( RH_CFG_SCREEN_WIDTH < 16 )
  #warning "Screen width may be too small."
#endif

#define GUI_Y_WIDTH                 RH_CFG_SCREEN_HEIGHT
#define GUI_X_WIDTH                 RH_CFG_SCREEN_WIDTH

/*===============================================================================================================
 * 定义对外API函数指针, 合计4个
 * [ glu_internal_draw_area    ] 给定区域, 以及该片区域的显存数据(内存重组对齐), 绘制在屏幕上
 * [ glu_internal_draw_pixel   ] 给定一个像素点, 在屏幕上绘制一个像素点
 * [ GUI_API_AssertParam ] 断言输出
 * [ GUI_API_DelayMs     ] (未使用)
===============================================================================================================*/

static void (*glu_internal_draw_area  )       (var x1,var y1,var x2,var y2,const GLU_TYPE(Pixel)* pixData) = NULL;
static void (*glu_internal_draw_pixel )       (var x,var y,const GLU_TYPE(Pixel) pixData) = NULL;
static void (*glu_internal_user_init  )       (void) = NULL;
static void (*glu_internal_user_disp  )       (void) = NULL;



#define M_SCREEN_MAIN   0
#define M_SCREEN_CNT    1


typedef BLK_SRCT(Stack)    __LINK_AreaRefreash;
typedef BLK_SRCT(LinkLoop) __LINK_WindowCFG;


/*===============================================================================================================
 * 根据配置的显存存放方式 RH_CFG_GRAM_TYPE 分配显存空间
 * [ RH_CFG_GRAM_INTERNAL] 如果配置为内置显存, 则根据颜色深度建立本地显存数组, 并将该数组首地址录入显存信息结构体 .GRAM
 * [ RH_CFG_GRAM_EXTADDR ] 如果配置为外置显存地址, 即给定内存绝对地址, ...
 * [ RH_CFG_GRAM_EXTSECT ] 如果配置为外置显存段, 即给定内存的分配段, ...
 * [ RH_CFG_GRAM_EXTPTR  ] 如果配置为外置显存指针, 即给定一个指针变量, 则直接将该指针录入显存信息结构体成员 .GRAM
===============================================================================================================*/
#pragma pack(1)
#if   ( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_INTERNAL )

    #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        static GLU_UION(Pixel) GRAM[M_SCREEN_CNT][ GUI_Y_WIDTH>>3 ][ GUI_X_WIDTH ];
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
        static GLU_UION(Pixel) GRAM[M_SCREEN_CNT][ GUI_Y_WIDTH ][ GUI_X_WIDTH ];
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        static GLU_UION(Pixel) GRAM[M_SCREEN_CNT][ GUI_Y_WIDTH ][ GUI_X_WIDTH ];
    #endif
#elif ( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_EXTADDR  )
    
#elif ( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_EXTSECT  )

#elif ( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_EXTPTR   )

#endif

/*===============================================================================================================
 * 配置显存信息结构体 Screen
 * .GRAM                     显存数据首地址, 由配置的颜色深度和屏幕大小决定其属性
 * .areaNeedRefreashHead     待刷新的区域信息链表头
 * .areaNeedRefreashPixelCnt 待刷新的像素点总数
===============================================================================================================*/
#pragma pack(1)
static struct{
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    GLU_UION(Pixel)    (*GRAM)[GUI_Y_WIDTH>>3][GUI_X_WIDTH];
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    GLU_UION(Pixel)    (*GRAM)[GUI_Y_WIDTH   ][GUI_X_WIDTH];
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    GLU_UION(Pixel)    (*GRAM)[GUI_Y_WIDTH   ][GUI_X_WIDTH];
#endif
    size_t           allocated_byte;

    bool             autoDisplay;

    __LINK_AreaRefreash*     areaNeedRefreashHead;
    size_t                   areaNeedRefreashCnt;
    size_t                   areaNeedRefreashPixelCnt;
    
    __LINK_WindowCFG*        windowCFG;

}Screen;

BLK_TYPE(Canvas) info_MainScreen = { //...//
    .h  = GUI_Y_WIDTH ,
    .w  = GUI_X_WIDTH ,
};

void GLU_FUNC( GUI, init )        ( void ){
    
    extern GLU_API void GLU_API_draw_area  ( var x1, var y1, var x2, var y2, const GLU_TYPE(Pixel)* pixData );
    extern GLU_API void GLU_API_draw_pixel ( var x, var y, const GLU_TYPE(Pixel) pixData );
    extern GLU_API void GLU_API_user_init  ( void );
    extern GLU_API void GLU_API_user_disp  ( void );
    
    glu_internal_draw_area     = GLU_API_draw_area;
    glu_internal_draw_pixel    = GLU_API_draw_pixel;
    glu_internal_user_init     = GLU_API_user_init;
    glu_internal_user_disp     = GLU_API_user_disp;
    
    glu_internal_user_init();
    
#if   ( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_INTERNAL )
    Screen.GRAM = GRAM;
#elif ( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_EXTADDR  )

#elif ( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_EXTSECT  )

#elif ( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_EXTPTR   )
    Screen.GRAM = (GLU_UION(Pixel) (*)[GUI_Y_WIDTH][GUI_X_WIDTH])RH_CFG_GRAM_POINTER;
#endif
    BLK_FUNC( Graph, init )();
    GLU_FUNC( Font , init )();

    info_MainScreen.ptr = Screen.GRAM[M_SCREEN_MAIN][0];
    
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    memset( Screen.GRAM , 0, M_SCREEN_CNT*(GUI_Y_WIDTH>>3)*GUI_X_WIDTH*sizeof(GLU_TYPE(Pixel)) );
    BLK_FUNC( Graph, set_color_depth   )  ( kBLK_ColorDepth_1Bit  );
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    memset( Screen.GRAM , 0, M_SCREEN_CNT*GUI_Y_WIDTH*GUI_X_WIDTH*sizeof(GLU_TYPE(Pixel)) );
    BLK_FUNC( Graph, set_color_depth   )  ( kBLK_ColorDepth_16Bit  );
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    memset( Screen.GRAM , 0, M_SCREEN_CNT*GUI_Y_WIDTH*GUI_X_WIDTH*sizeof(GLU_TYPE(Pixel)) );
    BLK_FUNC( Graph, set_color_depth   )  ( kBLK_ColorDepth_24Bit  );
#endif
    BLK_FUNC( Graph, set_render_method )  ( kBLK_RenderMethod_fill );

    Screen.autoDisplay = false;

    Screen.allocated_byte = 0;
    Screen.areaNeedRefreashHead = BLK_FUNC( Stack, createBase )( NULL );
    Screen.areaNeedRefreashCnt      = 0;
    Screen.areaNeedRefreashPixelCnt = 0;

    Screen.windowCFG = NULL;
}


/*===============================================================================================================
 * GLU_FUNC( GUI, refreashScreenArea )
 ================================================================================================================
 * 此函数将会调用显示屏API, 并立即在显示屏上显示图像.
 *
 * 以下情况,当API中支持区域刷新即 GLU_API_DrawArea不为NULL时:
 * 如果配置为内置显存, 那么图像数据将创建该区域的动态缓存,并从内置的 Screen.GRAM 中拷贝到其中(字节宽度对齐),刷新
   屏幕后释放动态缓存.
 * 如果配置为外置显存, 进死循环,暂未开发.
 *
 * 以下情况,当API不支持区域刷新, 仅有单个画点函数时即 glu_internal_draw_pixel :
 * 如果配置为内置显存, 那么图像数据将直接从 Screen.GRAM 逐一画点.
 * 如果配置为外置显存, 进死循环,暂未开发.
===============================================================================================================*/
void GLU_FUNC( GUI, refreashScreenArea )     ( var xs, var ys, var xe, var ye ){
#if( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_INTERNAL )
    // 内置显存需要向外导出数据
    if(glu_internal_draw_area != NULL){
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        const var x_width = xe-xs+1;
        const var ps      = ys>>3;
        const var pe      = ye>>3;
        const var p_width = pe-ps+1;
        GLU_TYPE(Pixel)* p = (GLU_TYPE(Pixel)*)RH_MALLOC((x_width)*(p_width)*sizeof(GLU_TYPE(Pixel)));
        BLK_FUNC( Memory, grbArea )(p, Screen.GRAM[M_SCREEN_MAIN][0] , sizeof(GLU_TYPE(Pixel)) , GUI_X_WIDTH, (int)xs, (int)ps, (int)xe, (int)pe  );
        
       (*glu_internal_draw_area)( xs , ys , xe , ye , p );

#else
        const var x_width = xe-xs+1;
        const var y_width = ye-ys+1;
        GLU_TYPE(Pixel)* p = (GLU_TYPE(Pixel)*)RH_MALLOC((x_width)*(y_width)*sizeof(GLU_TYPE(Pixel)));
        
        BLK_FUNC( Memory, grbArea )(p, Screen.GRAM[M_SCREEN_MAIN][0] , sizeof(GLU_TYPE(Pixel)), GUI_X_WIDTH, (int)xs, (int)ys, (int)xe, (int)ye);
        (*glu_internal_draw_area)( xs , ys , xe , ye , p);
#endif
        RH_FREE(p);
    }
    else{
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        for(int y=ys;y<=ye;y++)
            for(int x=xs;x<=xe;x++)
                (*glu_internal_draw_pixel)(x,y,Screen.GRAM[M_SCREEN_MAIN][y>>3][x].data);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
        RH_ASSERT(false);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        for(int y=ys;y<=ye;y++)
            for(int x=xs;x<=xe;x++)
                (*glu_internal_draw_pixel)(x,y,Screen.GRAM[M_SCREEN_MAIN][y][x].data);
#endif
    }
    
    if( GLU_GUI_isAutoDisplay() )
        (*glu_internal_user_disp)();
#else
    // 如果配置为外置显存, 则无需软件控制显示屏
    
#endif
}

void GLU_FUNC( GUI, EX_refreashScreenArea )   ( const __Area_t* area ){
    GLU_FUNC( GUI, refreashScreenArea )( area->xs, area->ys, area->xs+area->w-1, area->ys+area->h-1 );
}

/*==============================================================================================================
 * GLU_FUNC( GUI, refreashScreen )
 ===============================================================================================================
 * 此函数将会根据缓存情况进行屏幕刷新.
 *
 * Screen.areaNeedRefreashHead 是用于记载屏幕待刷新区域的链表表头, 表头本身不存储数据, 有效数据从下一节点开始.
   该链表表头于 GLU_FUNC( GUI, init ) 中被初始化. 该链表为栈链表, 类型为 <BLK_SRCT(Stack)>.
   GUI_RefreashScreenArea并且完成后将会释放其中的缓存图像数据及结构体自身.
 * 如果配置为内置显存, 那么将会判断屏幕总体待刷新像素点是否超过了屏幕像素总和, 如果超过了, 则释放所有链表节点,并刷新
   全屏幕,没有超过则将链表节点中数据即 <__Area_t> 结构体指针传入给 GLU_FUNC( GUI, refreashScreenArea ), 由于内置显存, 因此
   <__Area_t>结构体指针不会有图像数据.
 * 如果配置为外置显存, 进死循环,暂未开发.
===============================================================================================================*/
void GLU_FUNC( GUI, refreashScreen )         ( void ){
#if( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_INTERNAL )
    __exit( Screen.areaNeedRefreashHead == NULL );
    __Area_t *p = NULL;
    if( Screen.areaNeedRefreashPixelCnt >= GUI_X_WIDTH*GUI_Y_WIDTH ){
        GLU_FUNC( GUI, refreashScreenArea )( 0, 0, GUI_X_WIDTH-1, GUI_Y_WIDTH-1 );
        while( !BLK_FUNC( Stack, empty )( Screen.areaNeedRefreashHead ) ){
            p = BLK_FUNC( Stack, pop )( Screen.areaNeedRefreashHead );
            RH_FREE(p);
        }
    }else{
        while( !BLK_FUNC( Stack, empty )( Screen.areaNeedRefreashHead ) ){
            
            p = BLK_FUNC( Stack, pop )( Screen.areaNeedRefreashHead );
            GLU_FUNC( GUI, refreashScreenArea )( p->xs, p->ys, p->xs+p->w-1, p->ys+p->h-1 );
            RH_FREE(p);
        }
    }
    
    (*glu_internal_user_disp)();
    
    Screen.areaNeedRefreashPixelCnt = 0;
#endif
}

void GLU_FUNC( GUI, addScreenArea )          ( var xs, var ys, var xe, var ye ){
#if( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_INTERNAL )
    if( Screen.areaNeedRefreashPixelCnt >= GUI_X_WIDTH*GUI_Y_WIDTH ){
        __Area_t *p = NULL;
        while( !BLK_FUNC( Stack, empty )( Screen.areaNeedRefreashHead ) ){
            p = BLK_FUNC( Stack, pop )( Screen.areaNeedRefreashHead );
            RH_FREE(p);
        }
        return;
    }
    
    __Area_t* pArea = (__Area_t*)RH_MALLOC( sizeof(__Area_t) );
    pArea->xs = xs;
    pArea->ys = ys;
    pArea->w  = xe-xs+1;
    pArea->h  = ye-ys+1;
    Screen.areaNeedRefreashPixelCnt += pArea->w*pArea->h;
    if( Screen.areaNeedRefreashPixelCnt < GUI_X_WIDTH*GUI_Y_WIDTH )
        BLK_FUNC( Stack, push )( Screen.areaNeedRefreashHead, (void*)pArea );
#endif
}

void GLU_FUNC( GUI, EX_addScreenArea )( const __Area_t* area ){
#if( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_INTERNAL )
    if( Screen.areaNeedRefreashPixelCnt >= GUI_X_WIDTH*GUI_Y_WIDTH ){
        __Area_t *p = NULL;
        while( !BLK_FUNC( Stack, empty )( Screen.areaNeedRefreashHead ) ){
            p = BLK_FUNC( Stack, pop )( Screen.areaNeedRefreashHead );
            RH_FREE(p);
        }
        return;
    }
    
    RH_ASSERT(area);
    __Area_t* pArea = (__Area_t*)RH_MALLOC( sizeof(__Area_t) );
    memcpy( pArea, area, sizeof(__Area_t) );
    Screen.areaNeedRefreashPixelCnt += pArea->w*pArea->h;
    if( Screen.areaNeedRefreashPixelCnt < GUI_X_WIDTH*GUI_Y_WIDTH )
        BLK_FUNC( Stack, push )( Screen.areaNeedRefreashHead, (void*)pArea );
#endif
}

/*==============================================================================================================
 * GUI_RefreashEntireScreen
 ===============================================================================================================
 * 此函数将会刷新整屏.
 *
 * 此函数不会查看待刷新区域 Screen.areaNeedRefreashHead 的缓存情况, 直接清空链表, 并将显存内容全部刷新.
 * 如果配置为内置显存, 那么将会把Screen中的显存全部刷新, 无论是否有待刷新区域, 都会执行整屏刷新.
 * 如果配置为外置显存, 进死循环,暂未开发.
===============================================================================================================*/
void GLU_FUNC( GUI, refreashEntireScreen )  ( void ){
//    printf("%d %d\n",GUI_X_WIDTH,GUI_Y_WIDTH);
#if( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_INTERNAL )
    __Area_t *p = NULL;
    (*glu_internal_draw_area)( 0, 0, GUI_X_WIDTH-1, GUI_Y_WIDTH-1, (GLU_TYPE(Pixel)*)Screen.GRAM[M_SCREEN_MAIN][0] );
    while( !BLK_FUNC( Stack, empty )( Screen.areaNeedRefreashHead ) ){
        p = BLK_FUNC( Stack, pop   )( Screen.areaNeedRefreashHead );
        RH_FREE(p);
    }
#endif
    (*glu_internal_user_disp)();
}

void GLU_FUNC( GUI, setPenSize  )           ( size_t    penSize  ){
    BLK_FUNC( Graph, set_penSize ) ( penSize );
}

void GLU_FUNC( GUI, setPenColor )           ( uint32_t penColor ){
    BLK_FUNC( Graph, set_penColor )(penColor);
}

void GLU_FUNC( GUI, autoDisplay )           ( bool      cmd      ){
    if( cmd ){
        GLU_FUNC( GUI, refreashScreen )();
#ifdef RH_DEBUG
        RH_ASSERT( Screen.areaNeedRefreashCnt      == 0 );
        RH_ASSERT( Screen.areaNeedRefreashPixelCnt == 0 );
        RH_ASSERT( BLK_FUNC( Stack, empty )( Screen.areaNeedRefreashHead ) );
#endif
    }
    Screen.autoDisplay = cmd;
}

inline bool GLU_FUNC( GUI, isAutoDisplay  ) ( void ){
    return (bool)(Screen.autoDisplay==true);
}

inline bool GLU_FUNC( GUI, isInternalGRAM ) ( void ){
#if ( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_INTERNAL )
    return true;
#else
    return false;
#endif
}

inline bool GLU_FUNC( GUI, isCacheEmpty   ) ( void ){
    return BLK_FUNC( Stack, empty )( Screen.areaNeedRefreashHead );
}

void* GLU_FUNC( GUI, yield_GRAM )( void ){
    //...//
    return Screen.GRAM;
}




