#include <iostream>

#include "GridIO.h"
#include "MarchingCubes.h"
#include "GLatticeGenerator.h"

#include <ticktock.h>

#define PI 3.141592653589793

int main()
{

    GLatticeGenerator<double> m_g_generator(1, 1, 1);

    Eigen::Vector3<double> start(2 * PI, 0, 0.0);
    Eigen::Vector3<double> end(4 * PI, 2 * PI, 2 * PI);

    TICK(GenerateField)
    vector<vector<vector<double>>> g_field1 = m_g_generator.GenerateField(start.x(), start.y(), start.z(), end.x(), end.y(), end.z(), 21);
    TOCK(GenerateField)

    MarchingCubes<double> test {};
    test.init(start, end);

    TICK(MarchingCubesParallel)
    vector<vector<Vector3d>> parallel_result = test.GetSurfaceFromField(g_field1, 0.0f);
    TOCK(MarchingCubesParallel)

//    vector<vector<vector<double>>> g_field2 = m_g_generator.GenerateField(10, 0, 0, 20.0, 10.0, 10.0, 20);
//
//    test.init(Eigen::Vector3<double>(10.0, 0.0, 0.0), Eigen::Vector3<double>(20.0, 10.0, 10.0));

//    vector<vector<Vector3d>> parallel_result2 = test.GetSurfaceFromField(g_field2, 0.0f);
//
//    for (auto& f : parallel_result2)
//    {
//        parallel_result.push_back(f);
//    }

    TICK(MarchingCubesOutput)
    MarchingCubes<double>::write_triangleList_to_obj_reverseBackFront(parallel_result, "K:\\OpenGL\\Viewer1.07\\output\\g_field_parallel_4_cube.obj");
    TOCK(MarchingCubesOutput)

    return 0;
}






