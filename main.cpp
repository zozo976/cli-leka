/*#include <iostream>// c'est un header
#include <string>
#include <vector>

struct command_group {
    char start_sequence[4] = {0x2A, 0x2B, 0x2C, 0x2D};// tableau de taille fixe
    char length;
    std::vector<char> command; // tableau de taille variable
    char checksum;// char est sur 8 bits comme le checksum. Ainsi en cas d'erreurs on ne pourra pas avoir plus de 8 bits de checksum (un entier peut avoir 16 ou 32 bits)

    void print() {
        for (char c : start_sequence)// chacun des elts de start-sequence est stoké à son tour dans c c'est une copie donc modifier ce qui est dans c ne modifie pas start-sequence
            std::cout << std::hex << int(c) << " ";
        std::cout << std::hex << int(length) << " ";
        for (char c : command)
            std::cout << std::hex << int(c) << " ";
        std::cout << std::hex << int(checksum) << "\n";
    }
};

int main(int argc, char *argv[]) {

    std::cout << "argc: " << argc << "\n";

    for (int i = 0; i < argc; i++)
        std::cout << "argv: " << argv[i] << "\n";

    struct command_group cg;
    cg.length = 1;
    cg.command.push_back(0x70);//il n'y a qu'un seul bit dans le champ de checksum
    cg.checksum = 0x70;


    std::string info = "info";
    if (!info.compare(argv[1]))
        cg.print();
    return 0;
}
*/
#include <iostream>
#include <string>
#include <vector>



struct command_frame {
    unsigned start_sequence[4] = {0x2A, 0x2B, 0x2C, 0x2D};
    unsigned length;
    std::vector<unsigned> groupe_commandes;
    unsigned checksum;
/* Que ce soit la séquence de départ, la taille, chacun des éléments de command_groupe, ils sont sur 
1 byte donc sur 8 bits. Typer les variables en char ou en unsigned permet de les avoir sur 8 bits elles aussi*/
    command_frame(std::vector<std::string> &command_args) {
/* command_args est un tableau qui contient tous les argv à partir de argv[1]. Ainsi, command_args[0] = argv[1] 
soit la commande principale. commande_arg[1] et ainsi de suite contient les arguments quand il y en a. */
        int command_number = -1;
        std::vector<std::string> commandes = {"info", "stop.led", "stop.motor", "stop.robot","led.ear.all","led.ear.single","led.belt.all","led.belt.range","led.belt.single","motor.all","motor.duo","motor.left","moto.right","motivator","guidance"};

        if (!command_args.size()) { 
            std::cerr << "erreur: pas de commande donnée en argument\n";
            // erreur si la taille de command_args est nulle et donc qu'il ny' a aucune commande
            exit(1);
        }

        for (int i = 0; i < commandes.size(); i++)
            if (!commandes[i].compare(command_args[0]))
                command_number = i;
        // la commande principale rentrée dans command_args[0] est comparée à toutes les commandes jusqu'à la bonne
        if (command_number == 0) {
            length = 1;
        // Ici, la taille de la donnée vaut 1, il n' y a pas de Data
            groupe_commandes.push_back(0x70);

            checksum = 0x70;
        //Le checksum qui était sur 1 byte, après la fonction qui a pour but de le retraduire sur un byte sera le même.
        }

        if (command_number == 1) {
            length = 1;
            groupe_commandes.push_back(0xFD);
            checksum = 0xFD;
        }


        if (command_number == 2) {
            length = 1;
            groupe_commandes.push_back(0xFE);
            checksum = 0xFE;
        }


        
        if (command_number == 3) {
            length = 1;
            groupe_commandes.push_back(0xFF);
            checksum = 0xFF;
        }


        if (command_number == 4) {
            if (command_args.size() < 4) {
                std::cerr << "erreur: Il n'ya pas assez d'arguments\n";
                exit(1);
            }
            length = 4;
            // ici il y a la commande ainsi que les 3 arguments, ce qui fait une taille de 4 au total

            groupe_commandes.push_back(0x11);
            groupe_commandes.push_back(std::stoi(command_args[1]));
            groupe_commandes.push_back(std::stoi(command_args[2]));
            groupe_commandes.push_back(std::stoi(command_args[3]));
	    // On a donc un groupe de commande qui contient l'id ainsi que les différents arguments. 
            //checksum = checksum();
        }
	 if (command_number == 5) {
            if (command_args.size() < 5) {
                std::cerr << "erreur: il manque des arguments\n";
                exit(1);
            }
            length = 5;
            groupe_commandes.push_back(0x12);
            groupe_commandes.push_back(std::stoi(command_args[1]));
            groupe_commandes.push_back(std::stoi(command_args[2]));
            groupe_commandes.push_back(std::stoi(command_args[3]));
	    groupe_commandes.push_back(std::stoi(command_args[4]));
            
		
            //checksum = checksum();
        }

	
	 if (command_number == 6) {
            if (command_args.size() < 4) {
                std::cerr << "erreur: il manque des arguments\n";
                exit(1);
            }
            length = 4;
            groupe_commandes.push_back(0x13);
            groupe_commandes.push_back(std::stoi(command_args[1]));
            groupe_commandes.push_back(std::stoi(command_args[2]));
            groupe_commandes.push_back(std::stoi(command_args[3]));
	    
            //checksum = checksum();
        }


	 if (command_number == 7) {
            if (command_args.size() < 6) {
                std::cerr << "erreur: il manque des arguments\n";
                exit(1);
            }
            length = 6;
            groupe_commandes.push_back(0x14);
            groupe_commandes.push_back(std::stoi(command_args[1]));
            groupe_commandes.push_back(std::stoi(command_args[2]));
            groupe_commandes.push_back(std::stoi(command_args[3]));
	    groupe_commandes.push_back(std::stoi(command_args[4]));
	    groupe_commandes.push_back(std::stoi(command_args[5]));
	    
            //checksum = checksum();
        }
	 if (command_number == 8) {
            if (command_args.size() < 5) {
                std::cerr << "erreur: il manque des arguments\n";
                exit(1);
            }
            length = 5;
            groupe_commandes.push_back(0x15);
            groupe_commandes.push_back(std::stoi(command_args[1]));
            groupe_commandes.push_back(std::stoi(command_args[2]));
            groupe_commandes.push_back(std::stoi(command_args[3]));
	    groupe_commandes.push_back(std::stoi(command_args[4]));
	    
            //checksum = checksum();
        }
 if (command_number == 9) {
            if (command_args.size() < 3) {
                std::cerr << "erreur: il manque des arguments\n";
                exit(1);
            }
            length = 3;
            groupe_commandes.push_back(0x21);
            groupe_commandes.push_back(std::stoi(command_args[1]));
            groupe_commandes.push_back(std::stoi(command_args[2]));
            
	    
            //checksum = checksum();
        }
 if (command_number == 10) {
            if (command_args.size() < 5) {
                std::cerr << "erreur: il manque des arguments\n";
                exit(1);
            }
            length = 5;
            groupe_commandes.push_back(0x22);
            groupe_commandes.push_back(std::stoi(command_args[1]));
            groupe_commandes.push_back(std::stoi(command_args[2]));
            groupe_commandes.push_back(std::stoi(command_args[3]));
	    groupe_commandes.push_back(std::stoi(command_args[4]));
	    
            //checksum = checksum();
        }
 if (command_number == 11) {
            if (command_args.size() < 3) {
                std::cerr << "erreur: il manque des arguments\n";
                exit(1);
            }
            length = 3;
            groupe_commandes.push_back(0x23);
            groupe_commandes.push_back(std::stoi(command_args[1]));
            groupe_commandes.push_back(std::stoi(command_args[2]));
            
	    
            //checksum = checksum();
        }
 if (command_number == 12) {
            if (command_args.size() < 3) {
                std::cerr << "erreur: il manque des arguments\n";
                exit(1);
            }
            length = 3;
            groupe_commandes.push_back(0x24);
            groupe_commandes.push_back(std::stoi(command_args[1]));
            groupe_commandes.push_back(std::stoi(command_args[2]));
            groupe_commandes.push_back(std::stoi(command_args[3]));
	   
            //checksum = checksum();
        }
 if (command_number == 13) {
            if (command_args.size() < 2) {
                std::cerr << "erreur: il manque des arguments\n";
                exit(1);
            }
            length = 2;
            groupe_commandes.push_back(0x50);
            groupe_commandes.push_back(std::stoi(command_args[1]));
            
            
            //checksum = checksum();
        }
 if (command_number == 14) {
            if (command_args.size() < 2) {
                std::cerr << "erreur: il manque des arguments\n";
                exit(1);
            }
            length = 2;
            groupe_commandes.push_back(0x40);
            groupe_commandes.push_back(std::stoi(command_args[1]));
            
            
            //checksum = checksum();
        }
    }

    void print() {
        for (unsigned c : start_sequence)
            std::cout << std::hex << c << " ";
        std::cout << length << " ";
        for (unsigned c : groupe_commandes)
            std::cout << c << " ";
        std::cout << checksum << "\n";
    }
};

int main(int argc, char *argv[]) {
    // create vector of string containing the command and its arguments
    std::vector<std::string> command_args;
    for (int i = 1; i < argc; i++) {
        command_args.push_back(argv[i]);
    }

    struct command_frame cf(command_args);
    cf.print();

    return 0;
}
