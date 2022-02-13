#include <fstream>
#include <iostream>

#include "interface_noise_layers.h"


#define NOISE_LAYERS 10

interface_noise_layers :: interface_noise_layers(QWidget* parent) : QWidget(parent) {

    this -> setSizePolicy(QSizePolicy :: Expanding, QSizePolicy :: Fixed);

    box = new QVBoxLayout(this);
    box -> setSpacing(15);
    box -> setAlignment(Qt :: AlignTop);

    noise_layers_label = new QLabel("Noise Layers", this);
    noise_layers_label -> setAlignment(Qt::AlignCenter);
    noise_layers_label -> setFixedHeight(30);
    noise_layers_label -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); background-color: rgba(30, 33, 39, 1); height: 30px; margin: 0; }");

    box -> addWidget(noise_layers_label);

    for (int i = 0; i < NOISE_LAYERS; i++) {
        layers_vector.push_back(new interface_noise_layer(this, i + 1));
        box -> addWidget(layers_vector[i]);
    }

    layers_vector[0] -> activate_layer();

    update_new_layer_button();

}

void interface_noise_layers :: build_layers(int width, int height) {

    std :: vector < std :: vector <int> > heightmap(height, std :: vector <int> (width, 0));


    int ctr = 0;

    for (int i = 0; i < NOISE_LAYERS; i++) {
        if (layers_vector[i] -> active) {
            ctr ++;
            layers_vector[i] -> noise -> create_layer(width, height, layers_vector[i] -> frequency_spinbox -> value(), layers_vector[i] -> frequency_spinbox -> value(), 1);
//            layers_vector[i] -> noise -> create_layer(width, height,
//            width * layers_vector[i] -> frequency_spinbox -> value(), height * layers_vector[i] -> frequency_spinbox -> value(), 1);
//            layers_vector[i] -> noise

            for (int k = 0; k < height; k++) {
                for (int x = 0; x < width; x++) {
                    heightmap[k][x] += layers_vector[i] -> noise -> heightmap[k][x];
                   //std :: cout << heightmap[k][x] << "hmap val\n";
                }
            }
        }
    }


//    for (int k = 0; k < height; k++) {
//        for (int x = 0; x < width; x++) {
//            heightmap[k][x] = heightmap[k][x];
//           //std :: cout << heightmap[k][x] << "hmap val\n";
//        }
//    }

        std :: ofstream happy_file;
        happy_file.open("../terrain/heightmap2.pgm");
        happy_file << "P2\n";
        happy_file << width << ' ' << height << '\n';
        happy_file << "255\n";

        for (int i = 0; i < static_cast <int> (heightmap.size()); i++) {
            for (int k = 0; k < static_cast <int> (heightmap[0].size()); k++) {
                if (k == static_cast <int> (heightmap[0].size()) - 1) happy_file << heightmap[i][k] << '\n';
                else happy_file << heightmap[i][k] << ' ';
            }
        }
        happy_file.close();


}


void interface_noise_layers :: update_new_layer_button() {

    sort_layers();

    if (!layers_vector[1] -> active) layers_vector[0] -> delete_layer_button -> setEnabled(false);
    else layers_vector[0] -> delete_layer_button -> setEnabled(true);

    for (int i = 1; i < NOISE_LAYERS; i++) {
        if (layers_vector[i - 1] -> active && !layers_vector[i] -> active) {
            layers_vector[i] -> display_button();
            for (int k = i + 1; k < NOISE_LAYERS; k++) layers_vector[k] -> deactivate_layer();
            return;
        }
    }
}


void interface_noise_layers :: sort_layers() {

    for (int i = 0; i < NOISE_LAYERS; i++) {
        box -> removeWidget(layers_vector[i]);
        if (i < (NOISE_LAYERS - 1) && !layers_vector[i] -> active && layers_vector[i + 1] -> active) {
            layers_vector[NOISE_LAYERS] = layers_vector[i];
            layers_vector[i] = layers_vector[i + 1];
            layers_vector[i + 1] = layers_vector[NOISE_LAYERS];
        }
    }

    for (int i = 0; i < NOISE_LAYERS; i++) {
        layers_vector[i] -> layer_label -> setText(QString("Layer " + QString :: number(i + 1)));
        box -> addWidget(layers_vector[i]);
    }
}