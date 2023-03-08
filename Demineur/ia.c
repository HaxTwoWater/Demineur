//#include "DynamicArray.h"
//#include <cstddef>
//#include <stdarg.h>
//#include <stdio.h>
//
//typedef struct Ia
//{
//	DynamicArray* RevealPlayabled;
//	DynamicArray* FlagPlayabled;
//	DynamicArray* Groups;
//    int withIa;
//} Ia;
//
//Ia newIa()
//{
//	printf("Do you want to play with the IA ? (y/n) > ");
//	char ask = 122;
//    while (ask != 110 && ask != 121)
//    {
//        scanf_s("%c", &ask, 1);
//        while (getchar() != '\n');
//    }
//    Clear();
//    Ia ia;
//    ia.RevealPlayabled = InitDynamicArray(0, 0, 0);
//    ia.FlagPlayabled = InitDynamicArray(0, 0, 0);
//    ia.Groups = InitDynamicArray(0, 0, 0);
//    switch (ask)
//    {
//    case 110:
//        // Le joueur ne souhaite pas avoir une IA (110 = 'n')
//        ia.withIa = 0;
//        break;
//    case 121:
//        // Le joueur souhaite avoir une IA (121 = 'y')
//        ia.withIa = 1;
//        break;
//    }
//    return ia;
//}
//
//void CreateGroup(Ia* ia, int NumBombs, int CoordinateX, int CoordinateY, DynamicArray* Table)
//{
//    int startX = max(0, CoordinateX - 1);
//    int endX = min(Table->sizeX, CoordinateX + 2);
//    int startY = max(0, CoordinateY - 1);
//    int endY = min(Table->sizeY, CoordinateY + 2);
//
//    // Créer un groupe de coordonée
//    for (int a = startX; a < endX; a++)
//    {
//        for (int b = startY; b < endY; b++)
//        {
//            int index = convertCoordToLen(a, b, Table->sizeX);
//            if (Table->elm[index].val->reveal == 0)
//            {
//                // Ajouter la coordoné dans le groupe de coordonée
//            }
//        }
//    }
//}
//
//void CheckGroups(Ia* ia)
//{
//    int repeat = 1;
//    while (repeat)
//    {
//        repeat = 0;
//        for (int i = 0; i < ia->Groups->length; i++)
//        {
//            for (int j = i + 1; j < ia->Groups->length; j++)
//            {
//                if (ia->Groups->elm[i] == ia->Groups->elm[j])
//                {
//                    // Supprimer le groupe j
//					repeat = 1;
//                }
//                else
//                {
//
//                    ArrayElm a;
//                    ArrayElm b;
//                    if (ia->Groups->elm[i].length <= ia->Groups->elm[j].length)
//                    {
//                        a = ia->Groups->elm[i];
//                        b = ia->Groups->elm[j];
//                    }
//                    else
//                    {
//                        a = ia->Groups->elm[j];
//						b = ia->Groups->elm[i];
//                    }
//
//                    int verif = 0;
//                    DynamicArray* crossGroup = InitDynamicArray(0,0,0);
//                    for (int k = 0; k < a.length; k++)
//                    {
//                        for (int l = 0; l < b.length; l++)
//                        {
//                            if (a.elm[k] == b.elm[l])
//                            {
//								verif++;
//                                l = b.length;
//                                // Ajouter la coordoné dans crossGroup
//							}
//						}
//					}
//
//                    if (verif == a.length)
//                    {
//						// retirer les coordonnée du groupe a dans le groupe b
//                        // retirer le nombre de bombe du groupe a au groupe b
//                    }
//                    else if (verif != 0)
//                    {
//                        repeat = 1;
//
//                        int maxBombs = max(a.nbrBombs, b.nbrBombs);
//                        int minBombs = min(a.nbrBombs, b.nbrBombs);
//                        int nbrBombs;
//                        if (maxBombs == a.nbrBombs)
//                        {
//                            nbrBombs = maxBombs -b.length +verif;
//                        }
//                        else
//                        {
//							nbrBombs = maxBombs -a.length +verif;
//						}
//                        // créer un groupe avec les coordonnée de crossGroup et le nombre de bombe nbrBombs
//
//					}
//                }
//            }
//        }
//    }
//}
//
//int IaPlay(Ia* ia)
//{
//    for (int i = 0; i < ia->Groups->length; i++)
//    {
//        if (ia->Groups->elm[i].nbrBombs == ia->Groups->elm[i].length)
//        {
//			// Flag les coordonnée du groupe
//		}
//        else if (ia->Groups->elm[i].nbrBombs == 0)
//        {
//			// Reveal les coordonnée du groupe
//		}
//	}
//}