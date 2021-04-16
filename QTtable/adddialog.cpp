#include "adddialog.h"
#include <QtWidgets>

adddialog::adddialog(QWidget *parent)
    : QDialog(parent)
{

    startLabel = new QLabel("Start");
    endLabel = new QLabel("End");
    fhwmLabel = new QLabel("FWHM");
    netAreaLabel = new QLabel("NetArea");
    grossAreaLabel = new QLabel("GrossArea");
    centroidLabel = new QLabel("Centroid");
    uncertaintyLabel = new QLabel("Uncertainty");


    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    startText = new QLineEdit;
    endText = new QLineEdit;
    fhwmText = new QLineEdit;
    netAreaText = new QLineEdit;
    grossAreaText = new QLineEdit;
    centroidText = new QLineEdit;
    uncertaintyText = new QLineEdit;

    QGridLayout *gLayout = new QGridLayout;
    gLayout->setColumnStretch(1, 2);

    gLayout->addWidget(startLabel, 0, 0);
    gLayout->addWidget(startText, 0, 1);

    gLayout->addWidget(endLabel, 1, 0);
    gLayout->addWidget(endText, 1, 1);

    gLayout->addWidget(fhwmLabel, 2, 0);
    gLayout->addWidget(fhwmText, 2, 1);

    gLayout->addWidget(netAreaLabel, 3, 0);
    gLayout->addWidget(netAreaText, 3, 1);

    gLayout->addWidget(grossAreaLabel, 4, 0);
    gLayout->addWidget(grossAreaText, 4, 1);

    gLayout->addWidget(centroidLabel, 5, 0);
    gLayout->addWidget(centroidText, 5, 1);

    gLayout->addWidget(uncertaintyLabel, 6, 0);
    gLayout->addWidget(uncertaintyText, 6, 1);



    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle(tr("Add a Contact"));

}

