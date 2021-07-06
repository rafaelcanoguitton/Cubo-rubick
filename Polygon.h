
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include <iostream>
#include "Matrices.h"
using namespace std;

// ---------------------------------------------------------------------------------------------
struct Polygon{
    vector<float> vertices;
    vector<float> vertices_borders;
    ///
    vector<float> eje_x;
    vector<float> eje_y;
    vector<float> eje_z;
    ///
    int size_bits_polygon=0;
    int points_size=0;
    ///
    Polygon(vector<float> temp_vertices,float R,float G,float B){
        eje_x.reserve(2);
        eje_y.reserve(2);
        eje_z.reserve(2);
        eje_x.resize(2);
        eje_y.resize(2);
        eje_z.resize(2);
        vertices.reserve(temp_vertices.size()+((temp_vertices.size()/3)*5));
        for(int j=1;j<=temp_vertices.size();++j){
			vertices.push_back(temp_vertices[j-1]);
			//colores
			if(j%3==0){
                //colores
				vertices.push_back(R);
				vertices.push_back(G);
				vertices.push_back(B);
                //Texturas
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);

			}	
		}
        points_size=vertices.size()/8;
        vertices_borders=vertices;
        for(int i=0;i<points_size;i++){
            int pos=i*8;
            vertices_borders[pos+3]=0;
            vertices_borders[pos+4]=0;
            vertices_borders[pos+5]=0;
        }
        
        //directions.reserve((temp_vertices.size()/3)*2);
        //get_all_directions();
        size_bits_polygon=vertices.size()*sizeof(vertices);
        act_min_max_x();
        act_min_max_y();
        act_min_max_z();
        
    }
    ///
    void change_vertex_color(int position,float R,float G,float B){
        int pos=((position*2)+1)*3;
        vertices[pos]=R;
        vertices[pos+1]=G;
        vertices[pos+2]=B;
    }
    ///
    void change_polygon_color(float R,float G,float B){
        for(int i=0;i<points_size;i++){
            int pos=i*8;
            vertices[pos+3]=R;
            vertices[pos+4]=G;
            vertices[pos+5]=B;
        }
    }
    ///
    void change_texture_pos(float min_x,float min_y, float max_x,float max_y){
        vertices[6]=min_x;vertices[7]=min_y;
        vertices[14]=min_x;vertices[15]=max_y;
        vertices[22]=max_x;vertices[23]=max_y;
        vertices[30]=max_x;vertices[31]=min_y;
    }
    
    void draw(GLFWwindow* window,bool wired=false){
        glBufferData(GL_ARRAY_BUFFER, size_bits_polygon, vertices.data(), GL_DYNAMIC_DRAW);
        glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size()/8);   
        //borders
        if(wired==false){
            glLineWidth(8);
            glBufferData(GL_ARRAY_BUFFER, size_bits_polygon, vertices_borders.data(), GL_DYNAMIC_DRAW);
            glDrawArrays(GL_LINE_LOOP, 0, vertices_borders.size()/8);   
        }
        
            
    }
    
    void act_min_max_x(){
        vector<float> result;
        result.reserve(2);
        result.resize(2);
        result[0]=vertices[0];//min
        result[1]=vertices[0];//max
        for(int i=1;i<points_size;i++){
            int pos=i*8;
            if(vertices[pos]<result[0])
                result[0]=vertices[pos];
            if(vertices[pos]>result[1])
                result[1]=vertices[pos];
        }
        eje_x=result;
    }
    ///
    void act_min_max_y(){
        vector<float> result;
        result.reserve(2);
        result.resize(2);
        result[0]=vertices[1];//min
        result[1]=vertices[1];//max
        for(int i=1;i<points_size;i++){
            int pos=i*8;
            if(vertices[pos+1]<result[0])
                result[0]=vertices[pos+1];
            if(vertices[pos+1]>result[1])
                result[1]=vertices[pos+1];
        }
        eje_y=result;
    }
    ///
    void act_min_max_z(){
        vector<float> result;
        result.reserve(2);
        result.resize(2);
        result[0]=vertices[2];//min
        result[1]=vertices[2];//max
        for(int i=1;i<points_size;i++){
            int pos=i*8;
            if(vertices[pos+2]<result[0])
                result[0]=vertices[pos+2];
            if(vertices[pos+2]>result[1])
                result[1]=vertices[pos+2];
        }
        eje_z=result;
    }
    void print_min_max_axis(){
        cout<<eje_x[0]<<" "<<eje_x[1]<<endl;
        cout<<eje_y[0]<<" "<<eje_y[1]<<endl;
        cout<<eje_z[0]<<" "<<eje_z[1]<<endl;
        cout<<"//////////////////////////"<<endl;
    }
    ///
    void actualizar_ejes(){
        act_min_max_x();
        act_min_max_y();
        act_min_max_z();
    }
    ///
    void noob_translate(float new_x,float new_y,float new_z){
        for(int i=0;i<points_size;i++){
            int pos=i*8;
            vertices[pos]+=new_x;
            vertices[pos+1]+=new_y;
            vertices[pos+2]+=new_z;
            vertices_borders[pos]+=new_x;
            vertices_borders[pos+1]+=new_y;
            vertices_borders[pos+2]+=new_z;
        }
    }
    void pro_traslate(vector<float> point){//ready
        Matrix m1(4,4);
        Matrix m2(vertices);
        Matrix m3(4,4);
        m1.create_matrix_point(point);
        Multiply(m1,m2,m3);
        m3.export_to_vertex(vertices);
        m3.export_to_vertex(vertices_borders);
    }
    ///
    void pro_shear_origin(float angle){//ready
        Matrix m1(3,3);
        Matrix m2(vertices);
        Matrix m3(3,3);
        
        m1.convert_matrix_rotation_origin(angle);
        //m1.print_matrix();
        Multiply(m1,m2,m3);
        m3.export_to_vertex(vertices);
    }
    ///
    void pro_rotation_2d_x(float angle){
         Matrix m1(3,3);
        Matrix m2(vertices);
        Matrix m3(3,points_size);
        
        m1.convert_matrix_rotation_2d_x(angle);
        Multiply(m1,m2,m3);
        m3.export_to_vertex(vertices);
    }
    ///
    void pro_rotation_x(float angle){
        Matrix m1(4,4);
        Matrix m2(vertices);
        Matrix m3(4,points_size);

        m1.convert_matrix_rotation_x(angle);
        Multiply(m1,m2,m3);
        m3.export_to_vertex(vertices);
        m3.export_to_vertex(vertices_borders);
        
    }
    ///
    void pro_rotation_2d_y(float angle){
         Matrix m1(3,3);
        Matrix m2(vertices);
        Matrix m3(3,points_size);
        
        m1.convert_matrix_rotation_2d_y(angle);
        Multiply(m1,m2,m3);
        m3.export_to_vertex(vertices);
    }
    ///
    void pro_rotation_y(float angle){
        Matrix m1(4,4);
        Matrix m2(vertices);
        Matrix m3(4,points_size);
        
        m1.convert_matrix_rotation_y(angle);
        //m1.print_matrix();
        Multiply(m1,m2,m3);
        
        m3.export_to_vertex(vertices);
        m3.export_to_vertex(vertices_borders);
        
    }
    ///
    void pro_rotation_z(float angle){
        Matrix m1(4,4);
        Matrix m2(vertices);
        Matrix m3(4,points_size);
        
        m1.convert_matrix_rotation_z(angle);
        //m1.print_matrix();
        Multiply(m1,m2,m3);
        
        m3.export_to_vertex(vertices);
        m3.export_to_vertex(vertices_borders);
        
    }
    ///
    void pro_scale(float x,float y,float z){
        Matrix m1(4,4);
        Matrix m2(vertices);
        Matrix m3(4,points_size);
        
        m1.convert_matrix_scale(x,y,z);
        //m1.print_matrix();
        Multiply(m1,m2,m3);
        m3.print_matrix();
        m3.export_to_vertex(vertices);
    }
    void print_position(){
        char ejes[3]={'x','y','z'};
        for(int i=0;i<points_size;i++){
            int pos=i*8;
            cout<< ejes[i]<<": ";
            cout<<vertices[pos]<<"\t";
            cout<<vertices[pos+1]<<"\t";
            cout<<vertices[pos+2]<<endl;
        }
        cout<<"///////////////////////\n";
    }
};
