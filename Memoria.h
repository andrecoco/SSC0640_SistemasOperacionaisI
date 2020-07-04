#ifndef MEMORIA_H
#define MEMORIA_H
#include <vector>
#include <iostream>


//AS CLASSES
/*Moldura e Pagina eh onde a memoria realmente ta alocada*/
class Pagina {
public: //tudo antes disso eh private por default
    vector<char> dados; //o conte�do de endere�o vai ser representado por 1 byte
    int id;

    Pagina() { //Construtor default

    }

    //Demais Construtores
    Pagina(int id) { 
        this->id = id;
    }

    Pagina(int id, char dados) {
        this->id = id;
        this->dados = dados;
    }
};

class Moldura {
public: //tudo antes disso eh private por default
    Pagina pagina;

    Moldura() {     // Construtor
      //TODO
    }
};

class MemoriaSecundaria { //isso seria representando o disco, armazena as p�ginas virtuais
public: //tudo antes disso eh private por default
    vector<bool> paginasOcupadas; //guarda se cada pagina ta utilizada ou n
    vector<Pagina> paginas; //guardam as paginas de todos os processos

    MemoriaSecundaria() {     // Construtor
      //TODO
    }

    //retorna se a memoria esta cheia
    bool isFull() {
        for (int i = 0; i < paginasOcupadas.size(); i++)
            if (!paginasOcupadas[i]) //se tem alguma pagina livre
                return false;

        return true;
    }

    //retorna se existem pelo menos n paginas virtuais livres
    bool canFit(int n) {
        int contador = 0;

        for (int i = 0; i < paginasOcupadas.size() && contador <= n; i++)
            if (!paginasOcupadas[i]) //se essa pagina estiver livre
                contador++;

        return contador >= n;
    }

    //aloca n paginas e retorna o ID delas
    vector<int> criarPaginas(int n) {
        static int newPageId = 1;
        vector<int> paginasCriadas;

        for (int i = 0; i < n; i++) {
            Pagina *page = new Pagina(newPageId);
            if (page == NULL) { //se erro na criacao da pagina, id == -1
                paginasCriadas.push_back(-1);
                continue;
            } else {
                page->id = newPageId;
                newPageId++;
            }

            paginasCriadas.push_back(page->id);
        }
    }

    //atualiza a pagina por essa nova pagina passada
    int atualizaPagina(int IDPaginaVirtual, Pagina novaPagina) {
    	int index;
        Pagina *pagAntiga = buscaPagina(IDPaginaVirtual, &index);
        int atualizou = 0; //flag de verificacao

        if (pagAntiga->dados != novaPagina.dados) {
        	*pagAntiga = novaPagina;
        	atualizou = 1;
        }

        return atualizou;
    }

    //exclui a pagina com esse ID
    int deletaPagina(int IDPaginaVirtual) {
    	int index = -1; //indice da pagina desejada no vector de paginas
    	int deletou = 0; //flag de verificacao

    	Pagina *pag = buscaPagina(IDPaginaVirtual, &index);
    	if (pag->id != -1 && index != -1) {
    		paginas.erase(paginas.begin() + index);
    		deletou = 1;
    	}

    	return deletou;
    }

    //retorna uma copia da pagina com esse ID
    Pagina retornaPaginaPeloID(int IDPaginaVirtual) {
    	Pagina copia;

       for (int i = 0; i < paginas.size(); i++) {
            if (paginas[i].id == IDPaginaVirtual) {
                copia = paginas[i];
                return copia;
            }
       }

       return NULL;
    }

    //diferente da funcao acima, ela retorna a propria pagina, e nao uma copia
    Pagina* buscaPagina(int IDPaginaVirtual, int* index) {
    	Pagina *naoEncontrou = new Pagina(-1); //instancia uma pagina com id = -1, representando uma pagina inexistente

    	for (int i = 0; i < paginas.size(); i++) {
    		if (paginas[i].id == IDPaginaVirtual) {
    			*index = i;
            	return &(paginas[i]);
        	}
    	}

    	return naoEncontrou;
    }

};

class MemoriaPrincipal {

    public: //tudo antes disso eh private por default
    vector<bool> moldurasOcupadas; //guarda se cada moldura ta ocupada ou n
    vector<Moldura> molduras; //aqui seria tipo a memoria msm, "bruta"

    MemoriaPrincipal() {     // Construtor
      //TODO
    }

    //retorna se a memoria esta cheia
    bool isFull() {
        for (int i = 0; i < moldurasOcupadas.size(); i++)
            if (!moldurasOcupadas[i]) //se tem alguma moldura livre
                return false;

        return true;
    }

    //retornar uma copia da pagina nessa moldura
    Pagina retornaPagina(int IDMoldura) {
        //TODO
        Pagina teste;
        return teste;
    }

    //aloca a pagina na memoria principal, retorna o ID da pagina alocada (ou -1 caso a RAM esteja cheia)
    int alocarPagina(Pagina pagina) {
        //TODO
        return 0;
    }

    //desaloca essa pagina da RAM (recebe o id da moldura)
    int desalocarPagina(int id) {
        //TODO
        return 0;
    }
};

#endif