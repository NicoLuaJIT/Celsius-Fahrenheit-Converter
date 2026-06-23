#include <QApplication>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
/*
    Formulas:
    F = (C * 9/5) + 32
    C = (F - 32) * 5/9
*/

class Program : public QWidget
{
    Q_OBJECT
    private:
    // Initialize Widgets
        double result{};
        QVBoxLayout *layout{new QVBoxLayout(this)};
        QLineEdit *line{new QLineEdit(this)};
        QPushButton *fahrenheitToCelsiusBtn{new QPushButton("Fahrenheit to Celsius", this)};
        QPushButton *celsiusToFahrenHeitBtn{new QPushButton("Celsius To Fahrenheit", this)};
        QLabel *resultLabel{new QLabel("Result will appear here...", this)};
        QLabel *formulaC{new QLabel("C = (F - 32) * 5/9", this)};
        QLabel *formulaF{new QLabel("F = (C * 9/5) + 32", this)};
        QLabel *title{new QLabel("=== Celsius/Fahrenheit Converter ===", this)};

    // Initialize Functions
    void setLabelText(const QString &str)
    {
        resultLabel->setText(QString(str));
    }
    public:
        Program(QWidget *parent = nullptr) noexcept : QWidget(parent)
        {
            // Add Widgets to layout
            layout->addWidget(title);
            layout->addWidget(formulaC);
            layout->addWidget(formulaF);
            layout->addWidget(line);
            layout->addWidget(resultLabel);
            layout->addWidget(fahrenheitToCelsiusBtn);
            layout->addWidget(celsiusToFahrenHeitBtn);

            // Lambdas to deploy logic
            connect(fahrenheitToCelsiusBtn, &QPushButton::clicked, this, [this] {
                bool ok;
                double fahrenheit{line->text().toDouble(&ok)};

                if (!ok) {
                    QMessageBox::warning(this, "Error", "Please enter a valid number.");
                    return;
                }

                double result = (fahrenheit - 32.0) * 5.0/9.0;
                setLabelText(QString("Result: %1 °F").arg(result, 0, 'f', 2));
            });

            connect(celsiusToFahrenHeitBtn, &QPushButton::clicked, this, [this] {
                bool ok;
                double celsius{line->text().toDouble(&ok)};

                if (!ok) {
                    QMessageBox::warning(this, "Error", "Please enter a valid number.");
                    return;
                }

                double result = (celsius * 9.0/5.0) + 32.0;
                setLabelText(QString("Result: %1 °C").arg(result, 0, 'c', 2));
            });
        }
    
};

// Entry point
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    constexpr uint16_t width{300};
    constexpr uint16_t height{235};

    Program program;
    program.show();
    program.resize(width, height);

    return app.exec();
}

#include "main.moc" // <- Including MOC so that Qt stops bitching
