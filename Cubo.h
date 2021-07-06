#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Polygon.h"
using namespace std;
typedef vector<float> vec;
/*
void get_lados(vec &l1,vec &l2,vec &l3,vec &l4,vec A,vec B){
    //cara del frente
    l2.push_back(A[0]);l2.push_back(A[1]);l2.push_back(A[2]);
    l2.push_back(A[0]);l2.push_back(B[1]);l2.push_back(A[2]);
    l2.push_back(B[0]);l2.push_back(B[1]);l2.push_back(A[2]);
    l2.push_back(B[0]);l2.push_back(A[1]);l2.push_back(A[2]);
    //caras lados//derecho
    l1.push_back(B[0]);l1.push_back(A[1]);l1.push_back(B[2]);
    l1.push_back(B[0]);l1.push_back(B[1]);l1.push_back(B[2]);
    l1.push_back(B[0]);l1.push_back(B[1]);l1.push_back(A[2]);
    l1.push_back(B[0]);l1.push_back(A[1]);l1.push_back(A[2]);
    //cara de atras
    l3.push_back(A[0]);l3.push_back(A[1]);l3.push_back(B[2]);
    l3.push_back(A[0]);l3.push_back(B[1]);l3.push_back(B[2]);
    l3.push_back(B[0]);l3.push_back(B[1]);l3.push_back(B[2]);
    l3.push_back(B[0]);l3.push_back(A[1]);l3.push_back(B[2]);
    //caras lados//izquierdo
    l4.push_back(A[0]);l4.push_back(A[1]);l4.push_back(A[2]);
    l4.push_back(A[0]);l4.push_back(B[1]);l4.push_back(A[2]);
    l4.push_back(A[0]);l4.push_back(B[1]);l4.push_back(B[2]);
    l4.push_back(A[0]);l4.push_back(A[1]);l4.push_back(B[2]);
}
void get_tapa(vec &l5,vec &l6,vec A, vec B){
    //Tapa
    l5.push_back(B[0]);l5.push_back(B[1]);l5.push_back(A[2]);
    l5.push_back(B[0]);l5.push_back(B[1]);l5.push_back(B[2]);
    l5.push_back(A[0]);l5.push_back(B[1]);l5.push_back(B[2]);
    l5.push_back(A[0]);l5.push_back(B[1]);l5.push_back(A[2]);
    
    
    
    //Base
    l6.push_back(B[0]);l6.push_back(A[1]);l6.push_back(B[2]);  
    l6.push_back(B[0]);l6.push_back(A[1]);l6.push_back(A[2]);
    l6.push_back(A[0]);l6.push_back(A[1]);l6.push_back(A[2]);
    l6.push_back(A[0]);l6.push_back(A[1]);l6.push_back(B[2]);
    
    
         
}
*/
void get_lados(vec &l1,vec &l2,vec &l3,vec &l4,vec A,vec B){
    //cara del frente, atras
    l1.push_back(B[0]);l1.push_back(A[1]);l1.push_back(A[2]);
    l1.push_back(B[0]);l1.push_back(B[1]);l1.push_back(A[2]);
    l1.push_back(A[0]);l1.push_back(B[1]);l1.push_back(A[2]);
    l1.push_back(A[0]);l1.push_back(A[1]);l1.push_back(A[2]);
    //cara del atras
    l2.push_back(A[0]);l2.push_back(A[1]);l2.push_back(B[2]);
    l2.push_back(A[0]);l2.push_back(B[1]);l2.push_back(B[2]);
    l2.push_back(B[0]);l2.push_back(B[1]);l2.push_back(B[2]);
    l2.push_back(B[0]);l2.push_back(A[1]);l2.push_back(B[2]);
    //caras lados//derecho
    l3.push_back(B[0]);l3.push_back(A[1]);l3.push_back(B[2]);
    l3.push_back(B[0]);l3.push_back(B[1]);l3.push_back(B[2]);
    l3.push_back(B[0]);l3.push_back(B[1]);l3.push_back(A[2]);
    l3.push_back(B[0]);l3.push_back(A[1]);l3.push_back(A[2]);
    
    
    
    //caras lados//izquierdo
    l4.push_back(A[0]);l4.push_back(A[1]);l4.push_back(A[2]);
    l4.push_back(A[0]);l4.push_back(B[1]);l4.push_back(A[2]);
    l4.push_back(A[0]);l4.push_back(B[1]);l4.push_back(B[2]);
    l4.push_back(A[0]);l4.push_back(A[1]);l4.push_back(B[2]);
}
void get_tapa(vec &l5,vec &l6,vec A, vec B){
    //Tapa
    l5.push_back(A[0]);l5.push_back(B[1]);l5.push_back(B[2]);
    l5.push_back(A[0]);l5.push_back(B[1]);l5.push_back(A[2]);
    l5.push_back(B[0]);l5.push_back(B[1]);l5.push_back(A[2]);
    l5.push_back(B[0]);l5.push_back(B[1]);l5.push_back(B[2]);
    //Base
    l6.push_back(A[0]);l6.push_back(A[1]);l6.push_back(A[2]);
    l6.push_back(A[0]);l6.push_back(A[1]);l6.push_back(B[2]);
    l6.push_back(B[0]);l6.push_back(A[1]);l6.push_back(B[2]);
    l6.push_back(B[0]);l6.push_back(A[1]);l6.push_back(A[2]);
}
/*
//---------------------------------------------
void get_lados(vec &l1,vec &l2,vec &l3,vec &l4,vec A,vec B){
    //cara del frente, atras
    vec *ptr=&A;
    vec *cara=&l1;
    for(int i=0;i<2;++i){
        cara->push_back(A[0]);cara->push_back(A[1]);cara->push_back((*ptr)[2]);
        cara->push_back(A[0]);cara->push_back(B[1]);cara->push_back((*ptr)[2]);
        cara->push_back(B[0]);cara->push_back(B[1]);cara->push_back((*ptr)[2]);
        cara->push_back(B[0]);cara->push_back(A[1]);cara->push_back((*ptr)[2]);
        ptr=&B;
        cara=&l2;
    }
    //caras lados//derecho
    l3.push_back(B[0]);l3.push_back(A[1]);l3.push_back(A[2]);
    l3.push_back(B[0]);l3.push_back(B[1]);l3.push_back(A[2]);
    l3.push_back(B[0]);l3.push_back(B[1]);l3.push_back(B[2]);
    l3.push_back(B[0]);l3.push_back(A[1]);l3.push_back(B[2]);
    //caras lados//izquierdo
    l4.push_back(A[0]);l4.push_back(A[1]);l4.push_back(A[2]);
    l4.push_back(A[0]);l4.push_back(B[1]);l4.push_back(A[2]);
    l4.push_back(A[0]);l4.push_back(B[1]);l4.push_back(B[2]);
    l4.push_back(A[0]);l4.push_back(A[1]);l4.push_back(B[2]);
}
void get_tapa(vec &l5,vec &l6,vec A, vec B){
    //Tapa
    l5.push_back(A[0]);l5.push_back(B[1]);l5.push_back(A[2]);
    l5.push_back(B[0]);l5.push_back(B[1]);l5.push_back(A[2]);
    l5.push_back(B[0]);l5.push_back(B[1]);l5.push_back(B[2]);
    l5.push_back(A[0]);l5.push_back(B[1]);l5.push_back(B[2]);
    //Base
    l6.push_back(A[0]);l6.push_back(A[1]);l6.push_back(A[2]);
    l6.push_back(B[0]);l6.push_back(A[1]);l6.push_back(A[2]);
    l6.push_back(B[0]);l6.push_back(A[1]);l6.push_back(B[2]);
    l6.push_back(A[0]);l6.push_back(A[1]);l6.push_back(B[2]);
}
*/

struct Cubo{
    vector<Polygon> caras;
    vector<float> eje_x;
    vector<float> eje_y;
    vector<float> eje_z;
    Cubo(vec A,vec B){
        vec cara[6];
        caras.reserve(6);
        eje_x.reserve(2);
        eje_y.reserve(2);
        eje_z.reserve(2);
        eje_x.resize(2);
        eje_y.resize(2);
        eje_z.resize(2);
        for(int w=0;w<6;++w)
            cara[w].reserve(12);
        get_lados(cara[0],cara[1],cara[2],cara[3],A,B);
        get_tapa(cara[4],cara[5],A,B);
        for (int i=0;i<6;++i){
            //crear cada cara con el color gris default
            Polygon *ptr_poly=new Polygon(cara[i],0.512,0.512,0.512);
            caras.push_back(*ptr_poly);
        }
        /*
        for (int w=0;w<cara[0].size();++w){
            cout<<cara[4][w]<<endl;
            if((w+1)%3==0){
                cout<<"\n";
            }
        }
        */
        actualizar_ejes();
        
    }
    ///
    void draw(GLFWwindow* window,bool wired=false){
        for(int i=0;i<6;++i){
            caras[i].draw(window,wired);
        }
    }
    ///
    void print_cubo(){
        for(int i=0;i<6;++i){
            caras[i].print_position();
        }
    }
    ///
    void print_min_max_axis(){
        cout<<eje_x[0]<<" "<<eje_x[1]<<endl;
        cout<<eje_y[0]<<" "<<eje_y[1]<<endl;
        cout<<eje_z[0]<<" "<<eje_z[1]<<endl;
        cout<<"//////////////////////////////////"<<endl;
    }
    vector<float> get_x_min_max_cara(){
        return eje_x;
    }
    ///
    vector<float> get_y_min_max_cara(){
        return eje_y;
    }
    ///
    vector<float> get_z_min_max_cara(){
        return eje_z;
    }
    
    ///
    void change_color_cara(int position,float R,float G, float B){
        caras[position].change_polygon_color(R,G,B);
    }
    ///
    void change_textura_cara(int position,float min_x,float min_y, float max_x,float max_y){
        caras[position].change_texture_pos(min_x,min_y,max_x,max_y);
    }
    ///
    void actualizar_ejes(){
        for(int i=0;i<6;++i){
            caras[i].actualizar_ejes();
        }
        vector<float> new_x;
        vector<float> new_y;
        vector<float> new_z;
        for(int i=0;i<6;++i){
            new_x.insert(new_x.end(),caras[i].eje_x.begin(),caras[i].eje_x.end());
            new_y.insert(new_y.end(),caras[i].eje_y.begin(),caras[i].eje_y.end());
            new_z.insert(new_z.end(),caras[i].eje_z.begin(),caras[i].eje_z.end());
        }
        sort(new_x.begin(),new_x.end());
        sort(new_y.begin(),new_y.end());
        sort(new_z.begin(),new_z.end());
        eje_x[0]=new_x[0];
        eje_x[1]=new_x[11];

        eje_y[0]=new_y[0];
        eje_y[1]=new_y[11];

        eje_z[0]=new_z[0];
        eje_z[1]=new_z[11];
    }
    ///
    void rotate_x(float velocity){
        for(int i=0;i<6;++i){
            caras[i].pro_rotation_x(velocity);
        }
    }
    ///
    void trasladar(float x,float y, float z){
        for(int i=0;i<6;++i){
            caras[i].noob_translate(x,y,z);
        }
    }
    ///
    void rotate_y(float velocity){
        for(int i=0;i<6;++i){
            caras[i].pro_rotation_y(velocity);
        }
    }
    ///
    void rotate_z(float velocity){
        for(int i=0;i<6;++i){
            caras[i].pro_rotation_z(velocity);
        }
    }
};
