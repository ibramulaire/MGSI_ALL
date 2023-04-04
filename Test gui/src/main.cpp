// Dear ImGui: standalone example application for GLUT/FreeGLUT + OpenGL2, using legacy fixed pipeline
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

// !!! GLUT/FreeGLUT IS OBSOLETE PREHISTORIC SOFTWARE. Using GLUT is not recommended unless you really miss the 90's. !!!
// !!! If someone or something is teaching you GLUT today, you are being abused. Please show some resistance. !!!
// !!! Nowadays, prefer using GLFW or SDL instead!

// On Windows, you can install Freeglut using vcpkg:
//   git clone https://github.com/Microsoft/vcpkg
//   cd vcpkg
//   bootstrap - vcpkg.bat
//   vcpkg install freeglut --triplet=x86-windows   ; for win32
//   vcpkg install freeglut --triplet=x64-windows   ; for win64
//   vcpkg integrate install                        ; register include and libs in Visual Studio
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <armadillo>
#include<string>
using namespace arma;

#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl3.h"
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/freeglut.h>
#endif

#ifdef _MSC_VER
#pragma warning (disable: 4505) // unreferenced local function has been removed
#endif
using namespace std ;

typedef struct {

        double x;
        double y;
        double z;
       
} Sommet ;

int t=50 ;

// variables globales pour OpenGL
bool mouseLeftDown;
bool mouseRightDown;
bool mouseMiddleDown;
float mouseX, mouseY;
float cameraAngleX;
float cameraAngleY;
float cameraDistance=0.;
int n=1000000;
Sommet point[1000000];
Sommet point2[1000000];
Sommet S1={-1,0,1};
Sommet S2={1,0,0};
Sommet S3={0,2,-1};
Sommet Scourantr={0.5,0.5,1};
// Our state
static bool show_demo_window = true;
static bool show_another_window = true;
static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
static ImVec4 color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


void displayCourbe(void)
{
  for(int i=1;i<n;i++)
  {
   // cout<<point[i].x<<" "<<point[i].y<<" "<<point[i].z<<endl;
   glBegin(GL_POINTS);
   glColor3f(color.x,color.y,color.z);
   glVertex3f(point[i].x,point[i].y,point[i].z);
   glEnd();

    glBegin(GL_POINTS);
   glColor3f(0.0,1.0,0.0);
   glVertex3f(point2[i].x,point2[i].y,point2[i].z);
   //cout<<point2[i].x<<" "<<point2[i].y<<" "<<point2[i].z<<endl;
   glEnd();
  }
 }

void my_display_code()
{
    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        ImGui::ColorEdit3(" color", (float*)&color); 
        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }

   
}

void glut_display_func()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGLUT_NewFrame();

    my_display_code();

    // Rendering
    ImGui::Render();
    ImGuiIO& io = ImGui::GetIO();
    glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound, but prefer using the GL3+ code.
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    displayCourbe();
    glutSwapBuffers();
    glutPostRedisplay();
}




void calcules()
{


  
 
point[0]=Scourantr;
point2[0]=Scourantr;
  for(int i=1;i<n;i++)
  {
   int nrandom = rand() % 3 + 1;
  // cout<<nrandom<<endl;;
   if(nrandom==1)
   {
   point[i]={S1.x+ point[i-1].x/2,S1.y+point[i-1].y/2,S1.z+point[i-1].z/2};


   point2[i]={(S1.x+ point2[i-1].x/2)+S1.x- point2[i-1].x,(S1.y+point2[i-1].y/2)+S1.y-point2[i-1].y,(S1.z+point2[i-1].z/2)+S1.z-point2[i-1].z};
   }
   else 
    if(nrandom==2)
    {
   point[i]={S2.x+ point[i-1].x/2,S2.y+point[i-1].y/2,S2.z+point[i-1].z/2};
   point2[i]={(S2.x+ point2[i-1].x/2)+S2.x- point2[i-1].x,(S2.y+point2[i-1].y/2)+S2.y-point2[i-1].y,(S2.z+point2[i-1].z/2)+S2.z-point2[i-1].z};
    }
   else 
   {
    point[i]={S3.x+ point[i-1].x/2,S3.y+point[i-1].y/2,S3.z+point[i-1].z/2};
   point2[i]={(S3.x+ point2[i-1].x/2)+S3.x- point2[i-1].x,(S3.y+point2[i-1].y/2)+S3.y-point2[i-1].y,(S3.z+point2[i-1].z/2)+S3.z-point2[i-1].z};
   }

  }



}


 

// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.

int main(int argc, char** argv)
{
    // Create GLUT window
    glutInit(&argc, argv);
#ifdef __FREEGLUT_EXT_H__
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
#endif
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Dear ImGui GLUT+OpenGL3 Example");

    // Setup GLUT display function
    // We will also call ImGui_ImplGLUT_InstallFuncs() to get all the other functions installed for us,
    // otherwise it is possible to install our own functions and call the imgui_impl_glut.h functions ourselves.
    glutDisplayFunc(glut_display_func);

   
    

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    // FIXME: Consider reworking this example to install our own GLUT funcs + forward calls ImGui_ImplGLUT_XXX ones, instead of using ImGui_ImplGLUT_InstallFuncs().
    ImGui_ImplGLUT_Init();
    ImGui_ImplGLUT_InstallFuncs();
    ImGui_ImplOpenGL3_Init();

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);
    srand (time(NULL));
    calcules();
    glutMainLoop();

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
