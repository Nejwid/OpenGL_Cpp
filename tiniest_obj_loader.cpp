#include "tiniest_obj_loader.h"

void tiniest_obj_loader::load_obj(const std::string& filename)
{
    std::ifstream file(filename); // Otwieramy plik .obj

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string znacznik;
            iss >> znacznik;

            if (znacznik == "v") {
                Vertex vertex;
                iss >> vertex.x >> vertex.y >> vertex.z;
                v.push_back(vertex);

            }
            else if (znacznik == "vn") {
                Normal normal;
                iss >> normal.x >> normal.y >> normal.z;
                vn.push_back(normal);
            }
            else if (znacznik == "f") {
                std::vector<FaceVertex> faceVertices;
                FaceVertex fv;
                char delimiter;
                while (iss >> fv.vertexIndex) {
                    faceVertices.push_back(fv);
                    if (iss.peek() == '/') {
                        iss >> delimiter;
                        if (isdigit(iss.peek())) {
                            iss >> fv.normalIndex;
                        }
                        else {
                            fv.normalIndex = 0;
                        }
                    }
                    else {
                        fv.normalIndex = 0;
                    }
                    fv.vertexIndex--;
                    fv.normalIndex--;
                }
                f_v.push_back(faceVertices);
            }
        }
        file.close();

        for (const auto& faceVertices : f_v) {
            for (const auto& fv : faceVertices) {
                wierzcho³ki.push_back(fv.vertexIndex);
            }
        }
        for (int i = 0; i < wierzcho³ki.size(); i++)
        {
            Vertex vertex;
            int k = wierzcho³ki[i];
            k = k - 1;
            if (k < v.size())
            {
                vertex.x = v[k].x;
                vertex.y = v[k].y;
                vertex.z = v[k].z;
                wierzcho³ki_bufor.push_back(vertex);
            }
        }
        glGenBuffers(1, &wierzcho³ki_powtarzalne);
        glBindBuffer(GL_ARRAY_BUFFER, wierzcho³ki_powtarzalne);
        glBufferData(GL_ARRAY_BUFFER, wierzcho³ki_bufor.size() * sizeof(Vertex), wierzcho³ki_bufor.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); // Indeks 0, 3 wartoœci typu float, bez normalizacji, przesuniêcie jest 0
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    else {
        std::cerr << "Nie mo¿na otworzyæ pliku " << filename << " do odczytu." << std::endl;
    }
    for (const auto& vertex : v) {
        //std::cout << "x: " << f_v << ", y: " << vertex.y << ", z: " << vertex.z << std::endl;
    }
}

void tiniest_obj_loader::render_obj()
{
    glPushMatrix();
    glColor3f(0.5f, 0.4f, 0.8f);

    glTranslatef(0.6f, -1.4f, 2.f);
    //glScalef(0.03f, 0.03f, 0.03f);
    //glRotatef(90.0f, 0.0f, 1.0f, 0.0f);


    //przypisania do scian
    glBegin(GL_POLYGON);
    for (const auto& faceVertices : f_v) {
        for (const auto& fv : faceVertices) {
            const Vertex& vertex = v[fv.vertexIndex - 1];
            glVertex3f(vertex.x, vertex.y, vertex.z);
        }
    }
    glEnd();
    glPopMatrix();
}

void tiniest_obj_loader::render_obj_buffers()
{
    glPushMatrix();
    glColor3f(0.7f, 0.2f, 0.5f);
    glTranslatef(-0.6f, -1.4f, 2.f);
    //glScalef(0.003f, 0.003f, 0.003f);
    //po kolei 3 wierzcholki na trojkat
    glDrawArrays(GL_TRIANGLES, 0, wierzcho³ki_bufor.size());
    /*GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << error << std::endl;
    }*/
    glPopMatrix();
}

void tiniest_obj_loader::test_render()
{
    GLfloat vertices[] = {
        // Pozycje        // Kolory
        0.2f, -0.2f, 0.0f,
       -0.2f, -0.2f, 0.0f,
        0.0f,  0.2f, 0.0f,
    };

    // Utwórz bufor wierzcho³ków
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ARRAY_BUFFER, ebo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0); //  6 * sizeof(GLfloat) - odleglosc miedzy zestawami danych , (GLvoid*)0 - przesuniecie o 0 jednostek czyli dane czytamy do pierwszej pozycji
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDrawArrays(GL_POLYGON, 0, 3);
}


