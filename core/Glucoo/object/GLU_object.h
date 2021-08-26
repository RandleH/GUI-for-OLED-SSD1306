#ifndef _GLU_OBJECT_H
#define _GLU_OBJECT_H

#include "GLU_font.h"
#include "GLU_glucoo.h"

/*===============================================================================================================
 * 声明object插件的信息数据结构
===============================================================================================================*/
struct GLU_SRCT(Object){
    
    /*===================================================================================
     * Area --- This is a REQUIRED param. You must give a valid display area on screen.
                Once you submit the object infomation by using GUI_object_create, it
                can not be modified.
     ===================================================================================*/
    __Area_t             area;
    
    /*===================================================================================
     * widget --- This is a REQUIRED param. You must give a valid widget in the form of
                  <GLU_ENUM(ObjWidget)> enumeration. The widget determine lots of
                  attributions of an object.
     ===================================================================================*/
    GLU_ENUM(ObjWidget)    widget;
        
    /*===================================================================================
     * text --- This is an optional param. Only available when this widget has text
                (or number) to show.
     ===================================================================================*/
    GLU_SRCT(Text)       text;
    
    /*===================================================================================
     * Color --- Every objects has its background color.
     ===================================================================================*/
    GLU_TYPE(Pixel)      obj_color;
    GLU_TYPE(Pixel)      bk_color;
    
    /*===================================================================================
     * Data Source --- This parameter is speacifiled with widgets. It is a point to the
                       type like "__GUI_ObjDataSrc_xxxx" listed as following code.
     ===================================================================================*/
    void*   RH_ALLOCATED dataScr;

    /*===================================================================================
     * Data Source --- This parameter is speacifiled with widgets. It is a point to the
                       type like "__GUI_ObjDataSrc_xxxx" listed as following code.
     ===================================================================================*/
    void*   RH_ALLOCATED dataScr_init;

    /*===================================================================================
     * Allocated Method --- Please provide a memory allocating method in a form of 
                            callback function.
     ===================================================================================*/
    void *  RH_NULLABLE (*callmalloc)(size_t);
    void    RH_NULLABLE (*callfree  )(void *);
    
    /*===================================================================================
     * Shoe Frame (Deprecated)
     ===================================================================================*/
    bool                 showFrame;
    
    /*===================================================================================
     * NO MODIFY --- Do NOT modify the following parameters. It will be generated by
                     internal functions.
     ===================================================================================*/
    void (*insert_func)(const struct GLU_SRCT(Object)*);  // DO NOT MODIFY
    void (*remove_func)(const struct GLU_SRCT(Object)*);  // DO NOT MODIFY
    void (*adjust_func)(const struct GLU_SRCT(Object)*);  // DO NOT MODIFY
    const void*   const  cache;                           // DO NOT MODIFY
};
typedef struct GLU_SRCT(Object) GLU_SRCT(Object);

/*===============================================================================================================
 * 声明各个object所适配的输入数据结构
===============================================================================================================*/

struct __GUI_ObjDataScr_text{
    const char* text;
};
typedef struct __GUI_ObjDataScr_text __GUI_ObjDataScr_text;

struct __GUI_ObjDataScr_num{
    int32_t value;
};
typedef struct __GUI_ObjDataScr_num __GUI_ObjDataScr_num;

struct __GUI_ObjDataScr_fnum{
    float_t value;
};
typedef struct __GUI_ObjDataScr_fnum __GUI_ObjDataScr_fnum;

struct __GUI_ObjDataScr_switch{
    bool    cmd;
};
typedef struct __GUI_ObjDataScr_switch __GUI_ObjDataScr_switch;

struct __GUI_ObjDataScr_barH{
    int32_t value;
    int32_t max;
    int32_t min;
};
typedef struct __GUI_ObjDataScr_barH __GUI_ObjDataScr_barH;
typedef struct __GUI_ObjDataScr_barH __GUI_ObjDataScr_barV;
typedef struct __GUI_ObjDataScr_barH __GUI_ObjDataScr_trunk;

struct __GUI_ObjDataScr_joystick{
    int32_t value[2];   // 0:X; 1:Y
    int32_t max  [2];
    int32_t min  [2];
};
typedef struct __GUI_ObjDataScr_joystick __GUI_ObjDataScr_joystick;

struct __GUI_ObjDataScr_spinbox{
    int32_t     max;           // 数据上限
    int32_t     min;           // 数据下限
    int32_t     value;         // 数据值
    int16_t     text_offset;   // 以xs为起始量的偏移量
    int8_t      margin;        // 文字边缘留白量
    
    bool        active;        // 激活态
};
typedef struct __GUI_ObjDataScr_spinbox __GUI_ObjDataScr_spinbox;

struct __GUI_ObjDataScr_button{
    bool        cmd;           // 按钮状态
    var         radius;        // 按钮边缘半径
    bool        active;        // 激活态
};
typedef struct __GUI_ObjDataScr_button __GUI_ObjDataScr_button;

#endif
