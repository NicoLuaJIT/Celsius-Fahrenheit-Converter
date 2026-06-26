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
            setLayout(layout);
            
            layout->addWidget(title);
            layout->addWidget(formulaC);
            layout->addWidget(formulaF);
            layout->addWidget(line);
            layout->addWidget(resultLabel);
            layout->addWidget(fahrenheitToCelsiusBtn);
            layout->addWidget(celsiusToFahrenHeitBtn);

            line->setPlaceholderText("Enter your value here...");

            // Lambdas to deploy logic
            connect(fahrenheitToCelsiusBtn, &QPushButton::clicked, this, [this] {
                bool ok;
                double fahrenheit{line->text().toDouble(&ok)};

                if (!ok) {
                    QMessageBox::warning(this, "Error", "Please enter a valid number.");
                    return;
                }

                double result = (fahrenheit - 32.0) * 5.0/9.0;
                setLabelText(QString("Result: %1 °C").arg(result, 0, 'f', 2));
            });

            connect(celsiusToFahrenHeitBtn, &QPushButton::clicked, this, [this] {
                bool ok;
                double celsius{line->text().toDouble(&ok)};

                if (!ok) {
                    QMessageBox::warning(this, "Error", "Please enter a valid number.");
                    return;
                }

                double result = (celsius * 9.0/5.0) + 32.0;
                setLabelText(QString("Result: %1 °F").arg(result, 0, 'f', 2));
            });
        }
    
        // Styling
        void style(QApplication &app)
        {
            title->setStyleSheet("padding: 10px; color: rgb(210,220,230); border: 1.5px solid rgb(170,180,190); border-radius: 2.5px;");

            formulaC->setStyleSheet("color: rgb(210,220,230);");
            formulaF->setStyleSheet("color: rgb(210,220,230);");
            resultLabel->setStyleSheet("color: rgb(210,220,230);");

            line->setStyleSheet("color: rgb(210,220,230); background-color: rgb(95,96,97);");
            fahrenheitToCelsiusBtn->setStyleSheet("color: rgb(210,220,230); background-color: rgb(95,96,96);");
            celsiusToFahrenHeitBtn->setStyleSheet("color: rgb(210,220,230); background-color: rgb(95,96,97);");
            app.setStyleSheet("Program { background-color: rgb(45,46,47); }");
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
    program.style(app);
    program.resize(width, height);

    return app.exec();
}

#include "main.moc" // <- Including MOC so that Qt stops bitching
