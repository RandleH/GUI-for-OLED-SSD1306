
#include "../GLU_glucoo.h"

#include "BLK_graphic.h"

#define GUI_Y_WIDTH                 RH_CFG_SCREEN_HEIGHT
#define GUI_X_WIDTH                 RH_CFG_SCREEN_WIDTH
extern BLK_TYPE(Canvas) info_MainScreen; //...//

#define canvas info_MainScreen

void GLU_FUNC( GUI, rect_raw         )   ( int xs, int ys, int xe, int ye ){
#ifdef RH_DEBUG
#endif
    BLK_FUNC( Graph, rect_raw )( xs, ys, xe, ye, info_MainScreen.pBuffer, NULL );
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, refreashScreenArea )(xs, ys, xe, ye) : GLU_FUNC( GUI, addScreenArea )(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, rect_edged       )   ( int xs, int ys, int xe, int ye ){
#ifdef RH_DEBUG
#endif
    BLK_FUNC( Graph, rect_edged )( xs, ys, xe, ye, info_MainScreen.pBuffer, NULL );
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, refreashScreenArea )(xs, ys, xe, ye) : GLU_FUNC( GUI, addScreenArea )(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, rect_fill        )   ( int xs, int ys, int xe, int ye ){
#ifdef RH_DEBUG
#endif
    BLK_FUNC( Graph, rect_fill )( xs, ys, xe, ye, info_MainScreen.pBuffer, NULL );
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, refreashScreenArea )(xs, ys, xe, ye) : GLU_FUNC( GUI, addScreenArea )(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, rect_round_fill  )   ( int xs, int ys, int xe, int ye ){
#ifdef RH_DEBUG
#endif
    BLK_FUNC( Graph, rect_round_fill )( xs, ys, xe, ye, info_MainScreen.pBuffer, NULL );
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, refreashScreenArea )(xs, ys, xe, ye) : GLU_FUNC( GUI, addScreenArea )(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, circle_raw       )   ( int x , int y , int d ){
#ifdef RH_DEBUG
#endif
    int xs = RH_LIMIT( (x-(d>>1)-1), 0, GUI_X_WIDTH-1 );
    int xe = RH_LIMIT( (x+(d>>1)+1), 0, GUI_X_WIDTH-1 );
    int ys = RH_LIMIT( (y-(d>>1)-1), 0, GUI_Y_WIDTH-1 );
    int ye = RH_LIMIT( (y+(d>>1)+1), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_raw )( x, y, d, info_MainScreen.pBuffer, NULL );
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, refreashScreenArea )(xs, ys, xe, ye) : GLU_FUNC( GUI, addScreenArea )(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, circle_edged     )   ( int x , int y , int d ){
#ifdef RH_DEBUG
#endif
    int xs = RH_LIMIT( (x-(d>>1)-1), 0, GUI_X_WIDTH-1 );
    int xe = RH_LIMIT( (x+(d>>1)+1), 0, GUI_X_WIDTH-1 );
    int ys = RH_LIMIT( (y-(d>>1)-1), 0, GUI_Y_WIDTH-1 );
    int ye = RH_LIMIT( (y+(d>>1)+1), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_edged )( x, y, d, info_MainScreen.pBuffer, NULL );
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, refreashScreenArea )(xs, ys, xe, ye) : GLU_FUNC( GUI, addScreenArea )(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, circle_fill      )   ( int x , int y , int d ){
#ifdef RH_DEBUG
#endif
    int xs = RH_LIMIT( (x-(d>>1)-1), 0, GUI_X_WIDTH-1 );
    int xe = RH_LIMIT( (x+(d>>1)+1), 0, GUI_X_WIDTH-1 );
    int ys = RH_LIMIT( (y-(d>>1)-1), 0, GUI_Y_WIDTH-1 );
    int ye = RH_LIMIT( (y+(d>>1)+1), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_fill )( x, y, d, info_MainScreen.pBuffer, NULL );
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, refreashScreenArea )(xs, ys, xe, ye) : GLU_FUNC( GUI, addScreenArea )(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, circle_qrt1_fill )   ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = RH_LIMIT( (x    ), 0, GUI_X_WIDTH-1 );
    int xe = RH_LIMIT( (x+r+1), 0, GUI_X_WIDTH-1 );
    int ys = RH_LIMIT( (y-r-1), 0, GUI_Y_WIDTH-1 );
    int ye = RH_LIMIT( (y    ), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt1_fill )( x, y, r, info_MainScreen.pBuffer, NULL );
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, refreashScreenArea )(xs, ys, xe, ye) : GLU_FUNC( GUI, addScreenArea )(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, circle_qrt2_fill )   ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = RH_LIMIT( (x-r-1), 0, GUI_X_WIDTH-1 );
    int xe = RH_LIMIT( (x    ), 0, GUI_X_WIDTH-1 );
    int ys = RH_LIMIT( (y-r-1), 0, GUI_Y_WIDTH-1 );
    int ye = RH_LIMIT( (y    ), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt2_fill )( x, y, r, info_MainScreen.pBuffer, NULL );
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, refreashScreenArea )(xs, ys, xe, ye) : GLU_FUNC( GUI, addScreenArea )(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, circle_qrt3_fill )   ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = RH_LIMIT( (x-r-1), 0, GUI_X_WIDTH-1 );
    int xe = RH_LIMIT( (x    ), 0, GUI_X_WIDTH-1 );
    int ys = RH_LIMIT( (y    ), 0, GUI_Y_WIDTH-1 );
    int ye = RH_LIMIT( (y+r+1), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt3_fill )( x, y, r, info_MainScreen.pBuffer, NULL );
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, refreashScreenArea )(xs, ys, xe, ye) : GLU_FUNC( GUI, addScreenArea )(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, circle_qrt4_fill )   ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = RH_LIMIT( (x    ), 0, GUI_X_WIDTH-1 );
    int xe = RH_LIMIT( (x+r+1), 0, GUI_X_WIDTH-1 );
    int ys = RH_LIMIT( (y    ), 0, GUI_Y_WIDTH-1 );
    int ye = RH_LIMIT( (y+r+1), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt4_fill )( x, y, r, info_MainScreen.pBuffer, NULL );
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, refreashScreenArea )(xs, ys, xe, ye) : GLU_FUNC( GUI, addScreenArea )(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, circle_qrt1_raw  )   ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = RH_LIMIT( (x    ), 0, GUI_X_WIDTH-1 );
    int xe = RH_LIMIT( (x+r+1), 0, GUI_X_WIDTH-1 );
    int ys = RH_LIMIT( (y-r-1), 0, GUI_Y_WIDTH-1 );
    int ye = RH_LIMIT( (y    ), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt1_raw )( x, y, r, info_MainScreen.pBuffer, NULL );
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, refreashScreenArea )(xs, ys, xe, ye) : GLU_FUNC( GUI, addScreenArea )(xs, ys, xe, ye);
}
void GLU_FUNC( GUI, circle_qrt2_raw  )   ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = RH_LIMIT( (x-r-1), 0, GUI_X_WIDTH-1 );
    int xe = RH_LIMIT( (x    ), 0, GUI_X_WIDTH-1 );
    int ys = RH_LIMIT( (y-r-1), 0, GUI_Y_WIDTH-1 );
    int ye = RH_LIMIT( (y    ), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt2_raw )( x, y, r, info_MainScreen.pBuffer, NULL );
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, refreashScreenArea )(xs, ys, xe, ye) : GLU_FUNC( GUI, addScreenArea )(xs, ys, xe, ye);
}
void GLU_FUNC( GUI, circle_qrt3_raw  )   ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = RH_LIMIT( (x-r-1), 0, GUI_X_WIDTH-1 );
    int xe = RH_LIMIT( (x    ), 0, GUI_X_WIDTH-1 );
    int ys = RH_LIMIT( (y    ), 0, GUI_Y_WIDTH-1 );
    int ye = RH_LIMIT( (y+r+1), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt3_raw )( x, y, r, info_MainScreen.pBuffer, NULL );
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, refreashScreenArea )(xs, ys, xe, ye) : GLU_FUNC( GUI, addScreenArea )(xs, ys, xe, ye);
}
void GLU_FUNC( GUI, circle_qrt4_raw  )   ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = RH_LIMIT( (x    ), 0, GUI_X_WIDTH-1 );
    int xe = RH_LIMIT( (x+r+1), 0, GUI_X_WIDTH-1 );
    int ys = RH_LIMIT( (y    ), 0, GUI_Y_WIDTH-1 );
    int ye = RH_LIMIT( (y+r+1), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt4_raw )( x, y, r, info_MainScreen.pBuffer, NULL );
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, refreashScreenArea )(xs, ys, xe, ye) : GLU_FUNC( GUI, addScreenArea )(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, capsule_raw      )   ( int xs, int ys, int xe, int ye ){
    BLK_FUNC( Graph, capsule_raw )( xs, ys, xe, ye, info_MainScreen.pBuffer, NULL );
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, refreashScreenArea )(xs, ys, xe, ye) : GLU_FUNC( GUI, addScreenArea )(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, line_raw         )   ( int x1, int y1, int x2, int y2 ){
    BLK_FUNC( Graph, line_raw )( x1,y1,x2,y2, &canvas, NULL );
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, refreashScreenArea )(RH_MIN(x1, x2), RH_MIN(y1, y2), RH_MAX(x1, x2), RH_MAX(y1, y2)) : \
                           GLU_FUNC( GUI, addScreenArea )     (RH_MIN(x1, x2), RH_MIN(y1, y2), RH_MAX(x1, x2), RH_MAX(y1, y2));
}

void GLU_FUNC( GUI, quad_raw         )   ( int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4 ){
    
    int xs = RH_LIMIT( RH_MIN(x1, RH_MIN(x2, RH_MIN(x3, x4))), 0, GUI_X_WIDTH );
    int xe = RH_LIMIT( RH_MAX(x1, RH_MAX(x2, RH_MAX(x3, x4))), 0, GUI_X_WIDTH );
    int ys = RH_LIMIT( RH_MIN(y1, RH_MIN(y2, RH_MIN(y3, y4))), 0, GUI_Y_WIDTH );
    int ye = RH_LIMIT( RH_MAX(y1, RH_MAX(y2, RH_MAX(y3, y4))), 0, GUI_Y_WIDTH );
    
    BLK_FUNC( Graph, quad_raw )( x1, y1, x2, y2, x3, y3, x4, y4, &canvas, NULL );
    GLU_FUNC( GUI, isAutoDisplay )() ? \
        GLU_FUNC( GUI, refreashScreenArea )(xs,ys,xe,ye)
        :
        GLU_FUNC( GUI, addScreenArea      )(xs,ys,xe,ye);
}







