#include <iostream>
#include <vector>
#include "Cubo.h"
using namespace std;
int contador_solucion=-1;
string actual_animation="N";
struct Rubik{
    vector<Cubo> cubos;
    float animation_vel=0.1;
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
                    //cout<<i-2<<" "<<j-2<<" "<<k+2<<endl;
                    //cout<<i<<" "<<j<<" "<<k<<endl;
                    //cout<<"///////////////////////////////"<<endl;
                    Cubo *ptr_c=new Cubo({i-2,j-2,k+2},{i,j,k});
                    cubos.push_back(*ptr_c);
                }
            }   
        }
        /*
        change_textura_cara(0,0,0,0.165,1);//U
        change_textura_cara(1,0.165,0,0.33,1);//C
        change_textura_cara(2,0.33,0,0.495,1);//S
        change_textura_cara(3,0.495,0,0.66,1);//P
        change_textura_cara(4,0.66,0,0.825,1);//C
        change_textura_cara(5,0.825,0,1,1);//G
        */
        vector<float> tempo=get_texture_coord(0.33,0.5);
        //pintar verde cara 0
        for(int i=0;i<3;++i){
            int p_cubo=2+(i*3);
            int p_textura=12*i;
            //cout<<p_cubo<<" "<<p_cubo+9<<" "<<p_cubo+18<<endl;
            cubos[p_cubo].change_color_cara(0,0,1,0);
            cubos[p_cubo].change_textura_cara(0,tempo[p_textura],tempo[p_textura+1],tempo[p_textura+2],tempo[p_textura+3]);
            //
            cubos[p_cubo+9].change_color_cara(0,0,1,0);
            cubos[p_cubo+9].change_textura_cara(0,tempo[p_textura+4],tempo[p_textura+5],tempo[p_textura+6],tempo[p_textura+7]);
            //
            cubos[p_cubo+18].change_color_cara(0,0,1,0);
            cubos[p_cubo+18].change_textura_cara(0,tempo[p_textura+8],tempo[p_textura+9],tempo[p_textura+10],tempo[p_textura+11]);
            //
        }
        //
        //cubos[0].change_textura_cara(2,tempo[0],tempo[1],tempo[2],tempo[3]);
        //cubos[1].change_textura_cara(2,0.05,0.6,0.11,1);
        //cubos[2].change_textura_cara(2,0.11,0.6,0.165,1);
        //pintar azul cara 1
        //cout<<"cara "<<1<<endl;
        tempo=get_texture_coord(0,0.166);
        for(int i=0;i<3;++i){
            int p_cubo=18+(i*3);
            int p_t=12*i;
            cubos[p_cubo].change_color_cara(1,0,0,1);
            cubos[p_cubo].change_textura_cara(1,tempo[p_t],tempo[p_t+1],tempo[p_t+2],tempo[p_t+3]);
            cubos[p_cubo-9].change_color_cara(1,0,0,1);
            cubos[p_cubo-9].change_textura_cara(1,tempo[p_t+4],tempo[p_t+5],tempo[p_t+6],tempo[p_t+7]);
            cubos[p_cubo-18].change_color_cara(1,0,0,1);
            cubos[p_cubo-18].change_textura_cara(1,tempo[p_t+8],tempo[p_t+9],tempo[p_t+10],tempo[p_t+11]);
        }
        //pintar amarillo cara 2
        tempo=get_texture_coord(0.166,0.33);
        for(int i=0;i<9;++i){
            int p_t=4*i;
            cubos[i].change_color_cara(2,1,1,0);
            cubos[i].change_textura_cara(2,tempo[p_t],tempo[p_t+1],tempo[p_t+2],tempo[p_t+3]);
        }
        //pintar naranja cara 3
        tempo=get_texture_coord(0.5,0.66);
        for(int i=0;i<3;++i){
            int p_cubo=20+(i*3);
            int p_t=12*i;
            cubos[p_cubo].change_color_cara(3,1,0.5,0);
            cubos[p_cubo].change_textura_cara(3,tempo[p_t],tempo[p_t+1],tempo[p_t+2],tempo[p_t+3]);
            //
            cubos[p_cubo-1].change_color_cara(3,1,0.5,0);
            cubos[p_cubo-1].change_textura_cara(3,tempo[p_t+4],tempo[p_t+5],tempo[p_t+6],tempo[p_t+7]);
            //
            cubos[p_cubo-2].change_color_cara(3,1,0.5,0);
            cubos[p_cubo-2].change_textura_cara(3,tempo[p_t+8],tempo[p_t+9],tempo[p_t+10],tempo[p_t+11]);
            
        }

        //pintar rojo cara 4
        //cout<<"cara "<<4<<endl;
        tempo=get_texture_coord(0.166,0.33);
        for(int i=0;i<3;++i){
            int p_cubo=20-i;
            int p_t=12*i;
            //cout<<p_cubo<<" "<<p_cubo+1<<" "<<p_cubo+2<<endl;
            cubos[p_cubo].change_color_cara(4,1,0,0);
            cubos[p_cubo].change_textura_cara(4,tempo[p_t],tempo[p_t+1],tempo[p_t+2],tempo[p_t+3]);
            cubos[p_cubo-9].change_color_cara(4,1,0,0);
            cubos[p_cubo-9].change_textura_cara(4,tempo[p_t+4],tempo[p_t+5],tempo[p_t+6],tempo[p_t+7]);
            cubos[p_cubo-18].change_color_cara(4,1,0,0);
            cubos[p_cubo-18].change_textura_cara(4,tempo[p_t+8],tempo[p_t+9],tempo[p_t+10],tempo[p_t+11]);
        }
        //pintar blanco cara 5
        //cout<<"cara "<<5<<endl;
        tempo=get_texture_coord(0.825,1);
        for(int i=0;i<3;++i){
            int p_cubo=24+i;
            int p_t=12*i;
            //cout<<p_cubo<<" "<<p_cubo-9<<" "<<p_cubo-18<<endl;
            cubos[p_cubo].change_color_cara(5,1,1,1);
            cubos[p_cubo].change_textura_cara(5,tempo[p_t],tempo[p_t+1],tempo[p_t+2],tempo[p_t+3]);
            cubos[p_cubo-9].change_color_cara(5,1,1,1);
            cubos[p_cubo-9].change_textura_cara(5,tempo[p_t+4],tempo[p_t+5],tempo[p_t+6],tempo[p_t+7]);
            cubos[p_cubo-18].change_color_cara(5,1,1,1);
            cubos[p_cubo-18].change_textura_cara(5,tempo[p_t+8],tempo[p_t+9],tempo[p_t+10],tempo[p_t+11]);
        }
        
        cant_fps=90/animation_vel;
        actualizar_caras_pos();
        //print_eje();
        //cubos[0].print_cubo();
    }
    ///
    vector<float> get_texture_coord(float min_x, float max_x){
        vector<float> result;
        result.reserve(18);
        float x_temp=max_x-min_x;
        float x_pasos=x_temp/3;
        float y_pasos=1.0/3.0;
        //cout<<x_pasos<<"-"<<y_pasos<<endl;
        for(int j=0;j<3;++j){
            for(int i=0;i<3;++i){
                result.push_back((x_pasos*i)+min_x);
                result.push_back(1.0-(y_pasos*(j+1)));
                result.push_back((x_pasos*(i+1))+min_x);
                result.push_back((1.0)-(y_pasos*j));
                //cout<<"("<<(x_pasos*i)<<" - "<<1.0-(y_pasos*(j+1))<<")  ("<<x_pasos*(i+1)<<" - "<<(1.0)-(y_pasos*j)<<")"<<endl;
            }
            //cout<<"//////////////////////////////////////"<<endl;
        }
        return result;
    }
    ///
    void colorear_cubo(int pos,float r,float g,float b){
        for(int i=0;i<6;++i){
            cubos[pos].change_color_cara(i,r,g,b);
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
        if(reg_grados==0){
            for(int i=0;i<9;++i){
                F[i]->trasladar(0,0,-1);
            }
        }
        if(reg_grados!=cant_fps*veces){
            for(int i=0;i<9;++i){
                F[i]->rotate_z(-animation_vel);
            }
            reg_grados++;
            return "F";
        }
        reg_grados=0;
        for(int i=0;i<9;++i)
                F[i]->trasladar(0,0,1);
        actualizar_caras_pos();
        //print_eje();
        return "N";
    }
    string animation_R(int veces=1){
        if(reg_grados==0){
            for(int i=0;i<9;++i){
                R[i]->trasladar(1,0,0);
            }
        }
        if(reg_grados!=cant_fps*veces){
            for(int i=0;i<9;++i){
                R[i]->rotate_x(animation_vel);
            }
            reg_grados++;
            return "R";
        }
        reg_grados=0;
        for(int i=0;i<9;++i){
            R[i]->trasladar(-1,0,0);
        }
        actualizar_caras_pos();
        //print_eje();
        return "N";
    }
    string animation_U(int veces=1){
        if(reg_grados==0){
            for(int i=0;i<9;++i){
                U[i]->trasladar(0,1,0);
            }
        }
        if(reg_grados!=cant_fps*veces){
            for(int i=0;i<9;++i){
                U[i]->rotate_y(animation_vel);
            }
            reg_grados++;
            return "U";
        }
        reg_grados=0;
        for(int i=0;i<9;++i)
                U[i]->trasladar(0,-1,0);
        actualizar_caras_pos();
        //print_eje();
        return "N";
    }
    ///
    string animation_B(int veces=1){
        if(reg_grados==0){
            for(int i=0;i<9;++i){
                B[i]->trasladar(0,0,1);
            }
        }
        if(reg_grados!=cant_fps*veces){
            for(int i=0;i<9;++i){
                B[i]->rotate_z(animation_vel);
            }
            reg_grados++;
            return "B";
        }
        reg_grados=0;
        for(int i=0;i<9;++i){
            B[i]->trasladar(0,0,-1);
        }
        actualizar_caras_pos();
        //print_eje();
        return "N";
    }
    ///
    string animation_L(int veces=1){
        if(reg_grados==0){
            for(int i=0;i<9;++i){
                L[i]->trasladar(-1,0,0);
            }
        }
        if(reg_grados!=cant_fps*veces){
            for(int i=0;i<9;++i){
                L[i]->rotate_x(-animation_vel);
            }
            reg_grados++;
            return "L";
        }
        reg_grados=0;
        for(int i=0;i<9;++i)
                L[i]->trasladar(1,0,0);
        actualizar_caras_pos();
        //print_eje();
        return "N";
    }
    ///
    string animation_D(int veces=1){
        if(reg_grados==0){
            for(int i=0;i<9;++i){
                D[i]->trasladar(0,-1,0);
            }
        }
        if(reg_grados!=cant_fps*veces){
            for(int i=0;i<9;++i){
                D[i]->rotate_y(-animation_vel);
            }
            reg_grados++;
            return "D";
        }
        reg_grados=0;
        for(int i=0;i<9;++i)
                D[i]->trasladar(0,1,0);
        actualizar_caras_pos();
        //print_eje();
        return "N";
    }
    ///
    string aplicar_solucion(vector<string> &sol){
        if(actual_animation=="N"){
            //cout<<"contador_solucion "<<contador_solucion<<endl;
            contador_solucion++;
            if(contador_solucion==(sol.size())){
                contador_solucion=-1;
                sol.clear();
                return "E";
            }
            //cout<<"aplicando animacion->"<<xd[contador_solucion]<<"<-"<<endl;
        }
        //cout<<"("<<contador_solucion<<")"<<endl;
        actual_animation=sol[contador_solucion];
        
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