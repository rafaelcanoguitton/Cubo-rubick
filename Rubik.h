#include <iostream>
#include <vector>
#include "Cubo.h"
using namespace std;
int contador_solucion=-1;
string actual_animation="N";
struct Rubik{
    vector<Cubo> cubos;
    float animation_vel=0.3;
    float reg_grados=0,cant_fps;

    vector<Cubo*> U;
    vector<Cubo*> F;
    vector<Cubo*> B;
    vector<Cubo*> L;
    vector<Cubo*> R;
    vector<Cubo*> D;
    // 3,3,-3
    // -3,-3,3
    Rubik(){
        U.reserve(9);
        F.reserve(9);
        B.reserve(9);
        L.reserve(9);
        R.reserve(9);
        D.reserve(9);

        cubos.reserve(27);
        for(float i=3;i!=-3;i-=2){
            for(float j=3;j!=-3;j-=2){
                for(float k=-3;k!=3;k+=2){
                    Cubo *ptr_c=new Cubo({i-2,j-2,k+2},{i,j,k});
                    cubos.push_back(*ptr_c);
                }
            }   
        }
        //pintar verde cara 0
        for(int i=0;i<3;++i){
            int p_cubo=2+(i*9);
            cubos[p_cubo].change_color_cara(0,0,1,0);
            cubos[p_cubo+3].change_color_cara(0,0,1,0);
            cubos[p_cubo+6].change_color_cara(0,0,1,0);
        }
        //pintar azul cara 1
        for(int i=0;i<3;++i){
            int p_cubo=9*i;
            cubos[p_cubo].change_color_cara(1,0,0,1);
            cubos[p_cubo+3].change_color_cara(1,0,0,1);
            cubos[p_cubo+6].change_color_cara(1,0,0,1);
        }
        //pintar amarillo cara 2
        for(int i=0;i<9;++i){
            cubos[i].change_color_cara(2,1,1,0);
        }
        //pintar naranja cara 3
        for(int i=0;i<9;++i){
            cubos[18+i].change_color_cara(3,1,0.5,0);
        }
        //pintar rojo cara 4
        for(int i=0;i<3;++i){
            int p_cubo=9*i;
            cubos[p_cubo].change_color_cara(4,1,0,0);
            cubos[p_cubo+1].change_color_cara(4,1,0,0);
            cubos[p_cubo+2].change_color_cara(4,1,0,0);
        }
        //pintar blanco cara 5
        for(int i=0;i<3;++i){
            int p_cubo=6+i;
            cubos[p_cubo].change_color_cara(5,1,1,1);
            cubos[p_cubo+9].change_color_cara(5,1,1,1);
            cubos[p_cubo+18].change_color_cara(5,1,1,1);
        }
        cant_fps=90/animation_vel;
        actualizar_caras_pos();
        //print_eje();
        //cubos[0].print_cubo();
    }
    void get_side_R(){
        for(int i=0;i<27;++i){
            
        }
    }
    void colorear_cubo(int pos,float r,float g,float b){
        for(int i=0;i<6;++i){
            cubos[pos].change_color_cara(i,r,g,b);
        }
    }
    ///
    void actualizar_lados(){
        for(int i=0;i<27;++i){

        }
    }
    ///
    void colorear_cara_cubo(int num_cubo,int num_cara,float r,float g,float b){
        cubos[num_cubo].change_color_cara(num_cara,r,g,b);
    }
    //FRUBLD
    void draw(GLFWwindow* window,bool wired=false){
        for(int i=0;i<27;++i){
            cubos[i].draw(window,wired);
        }
    }
    void print_eje(){

        cout<<"U: "<<U.size()<<endl;
        cout<<"F: "<<F.size()<<endl;
        cout<<"B: "<<B.size()<<endl;
        cout<<"D: "<<D.size()<<endl;
        cout<<"L: "<<L.size()<<endl;
        cout<<"R: "<<R.size()<<endl;
        cout<<"/--------------------------------/\n";
    }
    //
    void actualizar_caras_pos(){
        L.clear();
        U.clear();
        F.clear();
        B.clear();
        L.clear();
        R.clear();
        D.clear();
        for(int i=0;i<27;++i){
            cubos[i].actualizar_ejes();
        }
        for(int i=0;i<27;++i){
            vector<float> new_eje_x=cubos[i].get_x_min_max_cara();
            //cout<<"cubo "<<i<<" : "<<new_eje_x[0]<<" = "<<new_eje_x[1]<<endl;
            if(new_eje_x[1]>2.8){
                R.push_back(&cubos[i]);
                //cout<<"cubo "<<i<<"-> R"<<endl;
            }
            if(new_eje_x[0]<-2.8){
                L.push_back(&cubos[i]);
                //cout<<"cubo "<<i<<"-> L"<<endl;
            }
            
        }
        for(int i=0;i<27;++i){
            vector<float> new_eje_y=cubos[i].get_y_min_max_cara();
            //cout<<"cubo "<<i<<" : "<<new_eje_y[0]<<" ={"<<new_eje_y[1]<<"}"<<endl;
            if(new_eje_y[1]>2.8){
                //cout<<"cubo "<<i<<"-> U"<<endl;
                U.push_back(&cubos[i]);
            }
            if(new_eje_y[0]<-2.8){
                //cout<<"cubo "<<i<<"-> D"<<endl;
                D.push_back(&cubos[i]);
            }
            
        }
        for(int i=0;i<27;++i){
            vector<float> new_eje_z=cubos[i].get_z_min_max_cara();
            //cout<<"cubo "<<i<<" : "<<new_eje_z[0]<<" = "<<new_eje_z[1]<<endl;
            if(new_eje_z[1]>2.8){
                //cout<<"cubo "<<i<<"-> B"<<endl;
                B.push_back(&cubos[i]);
            }
            if(new_eje_z[0]<-2.8){
                //cout<<"cubo "<<i<<"-> F"<<endl;
                F.push_back(&cubos[i]);
            }
        }
    }
    //
    string animation_F(int veces=1){
        if(reg_grados!=cant_fps*veces){
            for(int i=0;i<9;++i){
                F[i]->rotate_z(-animation_vel);
            }
            reg_grados++;
            return "F";
        }
        reg_grados=0;
        actualizar_caras_pos();
        //print_eje();
        return "N";
    }
    string animation_R(int veces=1){
        if(reg_grados!=cant_fps*veces){
            for(int i=0;i<9;++i){
                R[i]->rotate_x(animation_vel);
            }
            reg_grados++;
            return "R";
        }
        reg_grados=0;
        actualizar_caras_pos();
        //print_eje();
        return "N";
    }
    string animation_U(int veces=1){
        if(reg_grados!=cant_fps*veces){
            for(int i=0;i<9;++i){
                U[i]->rotate_y(animation_vel);
            }
            reg_grados++;
            return "U";
        }
        reg_grados=0;
        actualizar_caras_pos();
        //print_eje();
        return "N";
    }
    ///
    string animation_B(int veces=1){
        if(reg_grados!=cant_fps*veces){
            for(int i=0;i<9;++i){
                B[i]->rotate_z(animation_vel);
            }
            reg_grados++;
            return "B";
        }
        reg_grados=0;
        actualizar_caras_pos();
        //print_eje();
        return "N";
    }
    ///
    string animation_L(int veces=1){
        if(reg_grados!=cant_fps*veces){
            for(int i=0;i<9;++i){
                L[i]->rotate_x(-animation_vel);
            }
            reg_grados++;
            return "L";
        }
        reg_grados=0;
        actualizar_caras_pos();
        //print_eje();
        return "N";
    }
    ///
    string animation_D(int veces=1){
        if(reg_grados!=cant_fps*veces){
            for(int i=0;i<9;++i){
                D[i]->rotate_y(-animation_vel);
            }
            reg_grados++;
            return "D";
        }
        reg_grados=0;
        actualizar_caras_pos();
        //print_eje();
        return "N";
    }
    ///
    string aplicar_solucion(vector<string> &xd){
        
        
        if(actual_animation=="N"){
            //cout<<"contador_solucion "<<contador_solucion<<endl;
            contador_solucion++;
            if(contador_solucion==(xd.size())){
                contador_solucion=-1;
                xd.clear();
                return "N";
            }
            //cout<<"aplicando animacion->"<<xd[contador_solucion]<<"<-"<<endl;
        }
        
        
        
        //cout<<"("<<contador_solucion<<")"<<endl;
        actual_animation=xd[contador_solucion];
        
        //contador_solucion
        if(actual_animation=="R"){
            actual_animation=animation_R();
            return "A";
        }
        if(actual_animation=="R2"){
            actual_animation=animation_R(2);
            return "A";
        }
        if(actual_animation=="R'"){
            actual_animation=animation_R(3);
            return "A";
        }
        //================================================
        if(actual_animation=="U"){
            actual_animation=animation_U();
            return "A";
        }
        if(actual_animation=="U2"){
            actual_animation=animation_U(2);
            return "A";
        }
        if(actual_animation=="U'"){
            actual_animation=animation_U(3);
            return "A";
        }
        //================================================
        if(actual_animation=="D"){
            actual_animation=animation_D();
            return "A";
        }
        if(actual_animation=="D2"){
            actual_animation=animation_D(2);
            return "A";
        }
        if(actual_animation=="D'"){
            actual_animation=animation_D(3);
            return "A";
        }
        //================================================
        if(actual_animation=="F"){
            actual_animation=animation_F();
            return "A";
        }
        if(actual_animation=="F2"){
            actual_animation=animation_F(2);
            return "A";
        }
        if(actual_animation=="F'"){
            actual_animation=animation_F(3);
            return "A";
        }
        //================================================
        if(actual_animation=="B"){
            actual_animation=animation_B();
            return "A";
        }
        if(actual_animation=="B2"){
            actual_animation=animation_B(2);
            return "A";
        }
        if(actual_animation=="B'"){
            actual_animation=animation_B(3);
            return "A";
        }
        //================================================
        if(actual_animation=="L"){
            actual_animation=animation_L();
            return "A";
        }
        if(actual_animation=="L2"){
            actual_animation=animation_L(2);
            return "A";
        }
        if(actual_animation=="L'"){
            actual_animation=animation_L(3);
            return "A";
        }
        return "A";
    }
    ///
    void rotate_x(float grados){
        for(int i=0;i<27;++i){
            cubos[i].rotate_x(grados);
        }
    }
    void rotate_y(float grados){
        for(int i=0;i<27;++i){
            cubos[i].rotate_y(grados);
        }
    }
};