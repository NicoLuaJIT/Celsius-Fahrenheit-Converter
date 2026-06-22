#include <QApplication>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>

/*
    Formulas:
    F = (C * 9/5) + 32
    C = (F - 32) * 5/9
*/

class Program : public QWidget
{
    Q_OBJECT
    private:
        float result{0.0};
        QVBoxLayout *layout{new QVBoxLayout(this)};
        QLineEdit *line{new QLineEdit(this)};
        QPushButton *fahrenheitToCelsiusBtn{new QPushButton("Fahrenheit to Celsius", this)};
        QPushButton *celsiusToFahrenHeitBtn{new QPushButton("Celsius To Fahrenheit", this)};
        QLabel *resultLabel{new QLabel("Result: 0", this)};
        QLabel *formulaC{new QLabel("C = (F - 32) * 5/9", this)};
        QLabel *formulaF{new QLabel("F = (C * 9/5) + 32", this)};
        QLabel *title{new QLabel("=== Celsius/Fahrenheit Converter ===", this)};

    void setLabelText() noexcept
    {
        resultLabel->setText(QString("Result: %1").arg(result));
    }
    public:
        Program(QWidget *parent = nullptr) noexcept : QWidget(std::move(parent))
        {
            layout->addWidget(title);
            layout->addWidget(formulaC);
            layout->addWidget(formulaF);
            layout->addWidget(line);
            layout->addWidget(resultLabel);
            layout->addWidget(fahrenheitToCelsiusBtn);
            layout->addWidget(celsiusToFahrenHeitBtn);

            connect(fahrenheitToCelsiusBtn, &QPushButton::clicked, this, [this] {
                float fahrenheit{line->text().toFloat()};
                result = (fahrenheit - 32) * 5/9;
                setLabelText();
            });

            connect(celsiusToFahrenHeitBtn, &QPushButton::clicked, this, [this] {
                float celsius{line->text().toFloat()};
                result = (celsius * 9/5) + 32;
                setLabelText();
            });
        }
    
};


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

#include "main.moc"
