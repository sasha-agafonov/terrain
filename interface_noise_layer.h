#ifndef INTERFACE_NOISE_LAYER_H
#define INTERFACE_NOISE_LAYER_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>
#include <QObject>

#include "noise_layer.h"


class interface_noise_layer : public QFrame {

    Q_OBJECT

public:

    interface_noise_layer(QWidget* parent, int layer_number);

    QHBoxLayout* box;

    QPushButton* delete_layer_button;
    QPushButton* new_layer_button;

    QDoubleSpinBox* scale_spinbox;
    QSpinBox* frequency_spinbox;
    QDoubleSpinBox* persistence_spinbox;

    QComboBox* noise_type_combo;

    QLabel* layer_label;
    QLabel* empty_label;
    QLabel* scale_label;
    QLabel* frequency_label;
    QLabel* persistence_label;

    noise_layer* noise;

    bool active;

public slots:

    void activate_layer();
    void deactivate_layer();
    void display_button();

};

#endif // INTERFACE_NOISE_LAYER_H