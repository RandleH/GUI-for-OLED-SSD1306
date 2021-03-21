//
//  main.c
//  Xcode_12
//
//  Created by Randle.Helmslay on 2021/3/5.
//

#include <stdio.h>
#include "RH_common.h"
#include "RH_data.h"
#include "RH_gui.h"
#include "RH_gui_api.h"
#include "RH_font.h"

#include "RH_time.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    Simul_API_Init();

    GUI_RefreashScreen();


    __GUI_Window_t cfg2;
    cfg2.area.xs     = 200;
    cfg2.area.ys     = 140;
    cfg2.area.height = 130;
    cfg2.area.width  = 300;
    cfg2.type        = kGUI_WindowType_macOS;
    cfg2.size        = 40;
    cfg2.appearance  = kGUI_Appearance_Light;
    cfg2.title       = "a";
    cfg2.text        = NULL;//"Most people effortlessly recognize those digits as 504192. That ease is deceptive. In each hemisphere of our brain, humans have a primary visual cortex, also known as V1, containing 140 million neurons, with tens of billions of connections between them. And yet human vision involves not just V1, but an entire series of visual cortices - V2, V3, V4, and V5 - doing progressively more complex image processing. We carry in our heads a supercomputer, tuned by evolution over hundreds of millions of years, and superbly adapted to understand the visual world. Recognizing handwritten digits isn't easy. Rather, we humans are stupendously, astoundingly good at making sense of what our eyes show us. But nearly all that work is done unconsciously. And so we don't usually appreciate how tough a problem our visual systems solve.";

    ID_t ID_Window2 = GUI_create_window(&cfg2);

    GUI_insert_window( ID_Window2 );
    GUI_RefreashScreen();

    GUI_delete_window( ID_Window2 );

//    const size_t width = 300;
    const char* text = "Most people effortlessly recognize those digits as 504192. That ease is deceptive. In each hemisphere of our brain, humans have a primary visual cortex, also known as V1, containing 140 million neurons, with tens of billions of connections between them. And yet human vision involves not just V1, but an entire series of visual cortices - V2, V3, V4, and V5 - doing progressively more complex image processing. We carry in our heads a supercomputer, tuned by evolution over hundreds of millions of years, and superbly adapted to understand the visual world. Recognizing handwritten digits isn't easy. Rather, we humans are stupendously, astoundingly good at making sense of what our eyes show us. But nearly all that work is done unconsciously. And so we don't usually appreciate how tough a problem our visual systems solve.";
    __Font_exportText_Justify( text, 700 );
    return 0;
}
