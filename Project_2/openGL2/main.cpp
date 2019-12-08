#include <glad.h>
#include <glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "shader.h"
#include "camera.h"
#include "Point.h"

using namespace std;

const double PI = 3.141592653589793238462643383279502884197169399;

const unsigned int SCR_WIDTH = 1080;
const unsigned int SCR_HEIGHT = 810;

void getSphere();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Point getPoint(double u, double v);

GLuint WIDTH = 800, HEIGHT = 600;

int ustepNum = 100, vstepNum = 50;
vector<Point> points(2 + (vstepNum-1) * (ustepNum+1));
vector<int> indexes;

vector<float> coords(2 * (2 + (vstepNum - 1) * (ustepNum+1)));

Camera camera(glm::vec3(0.0f, -6.0f, 0.0f));

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        printf("Failure");

        glfwTerminate();
        return -1;
    }

    // Set the required callback functions
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Error");
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    /*
     * @TODO : use your own path here
     */
    Shader shader("../vert.glsl", "../frag.glsl");

    getSphere();

    // create the vertices
    float* vertices = new float[points.size() * 5];
    for (int i = 0; i < points.size() ; i++){
        /*
         *  --------------------------------------------
         * |  x  |  y  |  z  |  texture.x  | texture.y  |
         *  --------------------------------------------
         */
        vertices[5 * i] = points[i].x;
        vertices[5 * i + 1] = points[i].y;
        vertices[5 * i + 2] = points[i].z;
        vertices[5 * i + 3] = coords[2*i];
        vertices[5 * i + 4] = coords[2*i+1];
    }
    // copy the content of indexes to indices
    unsigned int * indices = new unsigned int[indexes.size()];
    for (int i = 0; i < indexes.size(); i++)
    {
        indices[i] = indexes[i];
    }


    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size() * 5 + 10, vertices, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexes.size(), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)( 3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);



    // load and create a texture
    /*
     * @TODO : use your own path here
     */
    string names[5] = { "../img/sun.jpg",
                        "../img/earth.jpg",
                        "../img/moon.jpg",
                        "../img/venus.jpg",
                        "../img/mercury.jpg"};
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned int textures[5] = {0};
    for (int i = 0; i < 5; i++)
    {
        glGenTextures(1, &textures[i]);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        unsigned char *data = stbi_load(string(names[i]).c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        // sun
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glUniform1i(glGetUniformLocation(shader.Program, "texture1"), 0);
        // earth
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        glUniform1i(glGetUniformLocation(shader.Program, "texture2"), 1);
        // moon
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, textures[2]);
        glUniform1i(glGetUniformLocation(shader.Program, "texture3"), 2);
        // venus
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, textures[3]);
        glUniform1i(glGetUniformLocation(shader.Program, "texture4"), 3);
        // mercury
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, textures[4]);
        glUniform1i(glGetUniformLocation(shader.Program, "texture5"), 4);

        glfwPollEvents();

        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation(shader.Program, "model");
        GLint viewLoc = glGetUniformLocation(shader.Program, "view");
        GLint projLoc = glGetUniformLocation(shader.Program, "projection");
        GLint indexLoc = glGetUniformLocation(shader.Program, "index");

        //model
        glm::mat4 model(1);
        model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));

        // Camera/View transformation
        glm::mat4 view(1);
        view = camera.GetViewMatrix();

        // Projection
        glm::mat4 projection(1);
        projection = glm::perspective(glm::radians(camera.Zoom), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

        glUniform1i(indexLoc, 0);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, 0);

        /*
         * draw the earth
         */

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(2.2f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));

        glUniform1i(indexLoc, 1);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, 0);

        /*
         * draw the moon
         */

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(2.0f, 0.5f, 0.0f));
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

        glUniform1i(indexLoc, 2);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, 0);

        /*
         * draw the venus
         */

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-1.6f, 0.0f, 0.4f));
        model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));

        glUniform1i(indexLoc, 3);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, 0);

        /*
         * draw the mercury
         */

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-1.0f, 0.8f, -0.8f));
        model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));

        glUniform1i(indexLoc, 4);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void getSphere(){
    double ustep = 1 / (double)ustepNum, vstep = 1 / (double)vstepNum;
    /*
     * put the three-dimensional coordinate into array "points"
     */
    points[0] = getPoint(0, 0);
    // the two-dim coordinate in texture (0.5, 1) is the midpoint of the top edge
    coords[0] = 0.5;
    coords[1] = 1;
    int c = 1;
    for (int i = 1; i < vstepNum; i++)
    {
        for (int j = 0; j <= ustepNum; j++)
        {
            points[c] = getPoint(ustep*j, vstep*i);
            coords[2 * c] = 1- ustep*j;
            coords[2 * c + 1 ] = vstep*i;
            c++;
        }
    }
    points[c] = getPoint(1, 1);
    // the two-dim coordinate in texture (0.5, 0) is the midpoint of the bottom edge
    coords[c++] = 0.5;
    coords[c] = 0;
    // top triangle
    for (int i = 0; i <= ustepNum ; i++)
    {
        /*
        *       0
        *       |\
        *       | \
        *       |__\
        *      i+1 (i+2)%(ustepnum+1)
        *
        */
        indexes.push_back(0);
        indexes.push_back(1 + i);
        indexes.push_back(1 + (i + 1) % (ustepNum+1));
    }
    // middle triangle
    for (int i = 1; i < vstepNum - 1; i++) {
        int start = 1 + (i - 1) * (ustepNum + 1);   // 起始索引号
        for (int j = start; j < start + (1 + ustepNum); j++) {

            /*
            *       j
            *       |\
            *       | \
            *       |__\
            *
            *j+ustepnum+1  j+(ustepnum + 1) + 1
            */
            indexes.push_back(j);
            indexes.push_back(j + (1 + ustepNum));
            indexes.push_back(start + (1+ustepNum) + (j + 1 - start) % (1+ustepNum));
            /*
            *
            *         j ___ j + 1
            *           \  |
            *		     \ |
            *		      \|
            *              `
            *     j + 1 + ustepnum + 1
            */

            indexes.push_back(j);
            indexes.push_back(start + (j + 1 - start) % (1+ustepNum));
            indexes.push_back(start + ustepNum + 1 + (j + 1 - start) %(1+ ustepNum));
        }
    }
    // bottom triangle
    int last = 1 + (ustepNum+1) * (vstepNum - 1);   // the last point
    int start = 1 + (ustepNum+1) * (vstepNum - 2);
    for (int i = 1 + (ustepNum+1) * (vstepNum - 2); i < 1 + ustepNum * (vstepNum - 1); i++)
    {
        /*
        *
        *         i ___ i+1
        *           \  |
        *		     \ |
        *		      \|
        *              `
        *            last
        */
        indexes.push_back(i);
        indexes.push_back(last);
        indexes.push_back(start + ((1 + i) - start) % (1+ustepNum));
    }
}

// Called whenever the size of windows is changed
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    WIDTH = width;
    HEIGHT = height;
    glViewport(0, 0, width, height);
}


Point getPoint(double u, double v){
    double x = sin(PI * v)*cos(2 * PI * u);
    double y = sin(PI * v)*sin(2 * PI * u);
    double z = cos(PI * v);
    return Point(x, y, z);
}