#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main()
{
    //Comentario
    
    string n1 = "yagoa.const@outlook.com.br";
    string n2 = "yagor1beiro1603@gmail.com";
    string n3 = "anajulia$@hotmail.org";
    string n4 = "yagoribeiro@alunos.utfpr.edu.br";

    regex padrao(R"(^[A-Za-z0-9._%+]+@[A-Za-z0-9.]+\.[A-Za-z]{2,4}$)");
    /**
     * R"( … )" = Raw string literal do C++: tudo que estiver entre R"( e )" é tomado literalmente, sem precisar escapar \, ", etc.
     * ^  = Inicio da linha
     * [A-Z-z0-9._%+] =  Qualquer caracter que seja letra ou numero e alguns caracteres especias . _ % +
     * + = 1 a N, quantificador
     * +@[A-Za-zo-9.] = ao menos 1 @ seguido de qualquer caracter 
     * +\.[A-Za-z]{2,} = ao menos um ponto seguido de letras(com,br,org,utfpr) com 2 a 4 caracteres
     * $  = fim da linha
     */

    if(regex_match(n1,padrao))
        cout << "N1 válida"<< endl;
    else
        cout << "N1 INVÁLIDA"<< endl;

        
    if(regex_match(n2,padrao))
    cout << "N2 válida"<< endl;
    else
    cout << "N2 INVÁLIDA"<< endl;

    
    if(regex_match(n3,padrao))
        cout << "N3 válida"<< endl;
    else
        cout << "N3 INVÁLIDA"<< endl;

        
    if(regex_match(n4,padrao))
    cout << "N4 válida"<< endl;
    else
    cout << "N4 INVÁLIDA"<< endl;


    string cpf1 = "13078529983";
    string cpf2 = "130.785.299-83";

    regex padrao2 (R"(^([0-9]{3}\.?){3}-?[0-9]{2}$)");
    /**
     * ^ = Inicio da linha
     * ([0-9]{3}) sequencia de tres numeros
     * ? 0 a 1 caracter, pode ter ou nao 
     * \.? tendo ou não .
     * {3} tres vezes (120.) (564.) (788.)
     * -? tendo ou nao -
     * [0-9]{2} sequencia de 2 numeros
     * $ fim da linha 
     */
    

    if(regex_match(cpf1,padrao2))
        cout << "cpf1 válida"<< endl;
    else
        cout << "cpf1 INVÁLIDA"<< endl;
        if(regex_match(cpf2,padrao2))
        cout << "cpf2 válido"<< endl;
    else
        cout << "cpf2 invalido"<< endl;

    regex cpfPattern(R"(^([0-9]{3}\.?){3}-?[0-9]{2}$)");

    if (regex_match(cpf1, cpfPattern))
    cout << "cpf1 válida\n";
    else
        cout << "cpf1 INVÁLIDA\n";

    if (regex_match(cpf2, cpfPattern))
        cout << "cpf2 válida\n";
    else
        cout << "cpf2 INVÁLIDA\n";

    std::regex senha(R"(^(?=.*[A-Z])(?=.*[0-9])(?=.*[^A-Za-z0-9]).{8,16}$)");
    /**
     * ^ = início da string
     * (?=.*[A-Z]) = lookahead: deve haver ao menos UMA letra maiúscula em qualquer posição
     * (?=.*[0-9]) = lookahead: deve haver ao menos UM dígito (0–9) em qualquer posição
     * (?=.*[^A-Za-z0-9])= lookahead: deve haver ao menos UM caractere não alfanumérico (símbolo especial)
     * .{8,16}=e, finalmente, devem ser consumidos de 8 a 16 caracteres quaisquer
     * $ = fim da string
     */
        
    return 0;

}