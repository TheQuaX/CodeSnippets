#include <stdio.h>
#include <stdlib.h>

#define PAGEMAXSIZE 8192
#define SMEMORYMAX 8388608
#define VMEMORYMAX 134217728
#define MAXPAGES 16384
#define MAXPAGEFRAMES 1024
#define MAXPAGEFRAMESIZE 8192


#define FRAME_TLB 0x80
#define FRAME_REFERENCED 0x20

/*
MMU         - übersetzt virtuelle Adresse in physikalische Adresse
TLB         - Translation Lookaside Buffer  |  V Gültigkeitsbit | FLAGS  | Physikalische Seitennummer  |
            - VAdresse teilen, Vordererteil (Seitennummer) = index zum nachschlagen, Eintrag + letzten Teil (Offset) zusammenfügen == physikalische Adresse
            - Flags: MMU löst Ausnahme bei nicht erlaubtem Zugriff aus


PageTable
TLB Entry
Process
ED-209


*/


struct TLBEntry{
    unsigned int page_index;
    unsigned int page_frame_index;
    unsigned char frame_attributes;
};

struct PageTableEntry{
    unsigned int page_frame_index;
    unsigned char frame_attributes;
};

struct PageTable{
    struct PageTableEntry** entries;
    unsigned int size;
};

struct TLB{
    struct TLBEntry** entries;
    unsigned int size;
};

struct Process{
    unsigned char process_id;
    struct PageTable* page_table;
};

struct MMU{
    struct TLB* tlb;
    struct Process* process;
};

struct ED_209{
    struct MMU* mmu;
};


/**
 * Aufgabe 7 startED209
 *
 * *ed 	- Referenz auf ED_209
 */
void startED209(struct ED_209* ed){
    //check if mmu contains a tlb with the valid instructions

     if (ed->mmu->tlb->entries[0]->page_frame_index == 0x3 && ed->mmu->tlb->entries[0]->page_index == 0x15 &&
        ed->mmu->tlb->entries[1]->page_frame_index == 0x1 && ed->mmu->tlb->entries[1]->page_index == 0x17f &&
        ed->mmu->tlb->entries[2]->page_frame_index == 0x4 && ed->mmu->tlb->entries[2]->page_index == 0x3ff &&
        ed->mmu->tlb->entries[3]->page_frame_index == 0x2 && ed->mmu->tlb->entries[3]->page_index == 0x152b &&
        ed->mmu->tlb->entries[4]->page_frame_index == 0x0 && ed->mmu->tlb->entries[4]->page_index == 0x2f77)
    {
        printf("ED-209 is working within normal parameters -> SIMULATION SUCCEEDED\n");

    }
    else
    {
        printf("ERROR: ED-209 is out of control -> SIMULATION FAILED\n");
    }

}

/**
 * Aufgabe 1 printSystemInfo - gibt Systeminformationen aus
 */
void printSystemInfo(){
    printf("+----------------------------------+\n| SystemInfo:\t\t\t   |\n");
    printf("| PageMaxSize\t\t%d\t   |\n", PAGEMAXSIZE);
    printf("| Pages\t\t\t%d\t   |\n", MAXPAGES);
    printf("| MaxPageFrames\t\t%d\t   |\n", MAXPAGEFRAMES);
    printf("| MaxPageFrameSize\t%d\t   |\n", MAXPAGEFRAMESIZE);
    printf("| MaxSystemMemory\t%d\t   |\n", SMEMORYMAX);
    printf("| MaxVirtualMemory\t%d  |\n", VMEMORYMAX);
    printf("+----------------------------------+\n\n");
}

/**
 * Aufgabe 2 createPageTable - erstellt eine Page Tabelle mit leeren Einträgen
 */
struct PageTable* createPageTable(){

    struct PageTable* tmp_pageTable;
    tmp_pageTable = malloc(sizeof(struct PageTable));

	tmp_pageTable->entries = malloc(sizeof(struct PageTableEntry*) * MAXPAGES);
	tmp_pageTable->size = MAXPAGES;

	for (int i = 0; i < MAXPAGES; i++) {
		tmp_pageTable->entries[i] = malloc(sizeof(struct PageTableEntry));
		tmp_pageTable->entries[i]->frame_attributes = 0x00;
		tmp_pageTable->entries[i]->page_frame_index = i;
	}

	printf("Created PageTable\n");

	return tmp_pageTable;
}

/**
 * Aufgabe 2 createTLB - erstellt einen TLB mit leeren Einträgen
 *
 * size	- Größe des TLBs
 */
struct TLB* createTLB(unsigned int size){

    struct TLB* tmp_TLB = malloc(sizeof(struct TLB));
    //Setting up tlb
    tmp_TLB->entries = malloc(sizeof(struct TLBEntry*) * size);
    tmp_TLB->size = size;

    for(int i = 0; i < size; i++){
        tmp_TLB->entries[i] = malloc(sizeof(struct TLBEntry));
        //clear all values
        tmp_TLB->entries[i]->frame_attributes = 0x00;
        tmp_TLB->entries[i]->page_frame_index = 0;
        tmp_TLB->entries[i]->page_index = i;
    }

    printf("Created TLB: sizeof '%d'\n", tmp_TLB->size);

    return tmp_TLB;

}

//Aufgabe 2 - Erstellt einen Prozess mit der ID id
struct Process* createProcess(unsigned char id){

    struct Process* tmp_Process = malloc(sizeof(struct Process));

    tmp_Process->process_id = id;
    tmp_Process->page_table = createPageTable();

    printf("Created Process: '%c'\n", tmp_Process->process_id);

    return tmp_Process;
}

//Aufgabe 3 - zählt die TLB-geflaggten Einträge eines pagetables innerhalb des Prozesses p
unsigned int countTLBEntries(struct Process* p) {
	int tmp_counter = 0;
	for (int i = 0; i < p->page_table->size; i++) {
		if (p->page_table->entries[i]->frame_attributes & FRAME_TLB) //bitwise AND
			tmp_counter ++;
	}
	return tmp_counter;
}


//Aufgabe 4 - kopiert alle Einträge der PageTable in den TLB
int copyTLBEntries(struct Process* p, struct TLB* tlb){//ehemals void, nun int Aufgbe 6 verschuldet

    //Error handler Aufgabe 5 (falls Eintäge > TLB size)
    if(tlb->size < countTLBEntries(p)){
        return -1;
    }

    int tlb_index = 0;

    //Loop through page table
    for(int i = 0; i < p->page_table->size; i++){

        if(p->page_table->entries[i]->frame_attributes & FRAME_TLB){ //bitwise AND falls als TLB geflaggt
            struct TLBEntry* tmp_TLBEntry = tlb->entries[tlb_index];

            tmp_TLBEntry->page_index = i;
            tmp_TLBEntry->frame_attributes = p->page_table->entries[i]->frame_attributes;
            tmp_TLBEntry->page_frame_index = p->page_table->entries[i]->page_frame_index;
            tlb_index++; //increase tlb index
        }



    }

    return 0;
}

//Aufgabe 5 - übersetzt eine virtuelle Adresse in eine physikalische Adresse
unsigned int translate(unsigned int virtual_address, struct PageTable* pt){

    unsigned int suffix = virtual_address % PAGEMAXSIZE;
    unsigned int prefix = virtual_address >> 10; // da 2^10 (Adressierung innerhalb einer Seite 1024Bit)

    unsigned int page_frame = pt->entries[prefix]->page_frame_index;//Shift führt dazu, dass die virtuelle Adresse extrahiert wird. Somit ergibt sich der Eintrag in der Tabelle.
    pt->entries[prefix]->frame_attributes |= FRAME_TLB | FRAME_REFERENCED; //Bitweises OR. Attribute werden hier beide gesetzt. Die Seite befindet sich nun in dem TLB
    unsigned int tmp = (page_frame << 10) + suffix;
    //page_frame ist nun die physikalische Adresse; wird also um 10 Bit nach links verschoben.
    //suffix bleibt identisch, da Page und Page Frame gleich groß sind.

    return tmp;
}

//Aufgabe 6 - liest Instruktionen und rechnet in physikalische Adressen um. Kopiert alle Referenzeinträge in den TLB.
int preprocessInstructions(struct MMU* mmu, unsigned int* instructions, unsigned int instruction_count) {

    //Info
    printf("\nFixing MMU\n");
	int page_frame_index = 0;
	for (int i = 0; i < instruction_count; i++) {

        //command input bitmasken
		int offset = instructions[i] & 0x00FFFFFF;//(1, falls beide Bits 1 sind, ansonsten 0) führt zur Extraction der Adresse
		int page = instructions[i] & 0xFF000000;//führt zur Extraction des Befehls

		//momentan umgehung von translate
		unsigned int suffix = offset % PAGEMAXSIZE;
		unsigned int prefix = offset >> 10; // 10 Bit innerhalb Page

		//kopiert Einträge in TLB von der MMU
		// Eintrag Platz in TLB und Page Frame zuweisen, sofern noch nicht geschehen
		if (!(mmu->process->page_table->entries[prefix]->frame_attributes & FRAME_TLB)) {
			mmu->process->page_table->entries[prefix]->page_frame_index = page_frame_index;
			page_frame_index++;
			mmu->process->page_table->entries[prefix]->frame_attributes |= FRAME_TLB; //Bitwise inclusive OR and !!assignment!! operator
		}
		instructions[i] = page | (mmu->process->page_table->entries[prefix]->page_frame_index << 10) | suffix; //tut
	}

	printf("Fixed MMU\n");
	//// Einträge Kopieren und Erfolg zurückgeben
	return copyTLBEntries(mmu->process, mmu->tlb);
}


unsigned int edSimulation [5]  = { 0xBDDE10 , 0x5FFFE , 0x54AC01 , 0x540C , 0xFFFFE } ;



int main()
{
    printSystemInfo();
    struct ED_209* ed = malloc(sizeof(struct ED_209));
    ed->mmu = malloc(sizeof(struct MMU));
    ed->mmu->process = createProcess('1');
    ed->mmu->tlb = createTLB(MAXPAGES);

    //Test ohne preprocess
    printf("\nRunning simulation without preprocess:\n");
    startED209(ed);

    //ausführen von preprocess
    preprocessInstructions(ed->mmu,edSimulation,5);
    printf("\nSTARTING TEST-SIMULATION AFTER PREPROCESS:\n");
    startED209(ed);
    free(ed);
    return 0;
}
