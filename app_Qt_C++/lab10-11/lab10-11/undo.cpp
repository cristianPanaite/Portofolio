#include "undo.h"

void UndoAdauga::doUndo()
{
	repo.stergere(d_adaugata);
}

void UndoStergere::doUndo()
{
	repo.store(d_stearsa);
}

void UndoMod::doUndo()
{
	repo.modify(d1, d2);
}

void UndoAddContract::doUndo()
{
	cont.sterge(nume);
}
