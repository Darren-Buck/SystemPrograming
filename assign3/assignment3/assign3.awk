
BEGIN {
FS = ",";
type1 = 0;
type2 = 0;
type3 = 0;
type4 = 0;
type5 = 0;
type6 = 0;
type7 = 0;
type8 = 0;
type9 = 0;
type10 = 0;
type11 = 0;
type12 = 0;
i = 1;
prue = 0;
south = 0;
west = 0;
north = 0;
central = 0;
firstRec = "";
lastRec = "";
}
{

switch($3){

   case "Theft":
     type1++;
     break
   case "\"Assist the Public\"":
     type2++;
     break
   case "\"Traffic Related\"":
     type3++;
     break
   case "\"Ordinance Violation\"":
     type4++;
     break
   case "\"Shoplifting In Progress\"":
     type5++;
     break
   case "\"Burglary Vehicle\"":
     type6++;
     break
   case "\"Disturbance \"":
     type7++;
     break
   case "\"Welfare Check\"":
     type8++;
     break
   case "Threats":
     type9++;
     break
   case "\"Criminal Mischief\"":
     type10++;
     break
   case "\"Animal Related\"":
     type11++;
     break
   case "Information":
     type12++;
     break
   default:
     break;
  } 
switch($5){

  case "PRUE":
    prue++;
    break
  case "SOUTH":
    south++;
    break
  case "WEST":
    west++;
    break
  case "NORTH":
    north++;
    break
  case "CENTRAL":
    central++;
    break
  default:
    break
  }

if (NR==1){
firstRec = $0;
date = substr($2,2,10);
}
if (NR = FNR){
lastRec = $0;
}

}
END{
printf("\n\nTotal calls: %d\n\n",FNR);

printf("Date: %s\n",date);
printf("First Call: %s\n",firstRec);
printf("Last Call: %s\n\n",lastRec);

printf("Per-problem totals:\n");
printf("\tTheft: %d\n",type1);
printf("\t\"Assist the Public\": %d\n", type2);
printf("\t\"Traffic Related\": %d\n", type3);
printf("\t\"Ordinance Violation\": %d\n", type4);
printf("\t\"Shoplifting In Progress\": %d\n", type5);
printf("\t\"Burglary Vehicle\": %d\n", type6);
printf("\tDisturbance: %d\n", type7);
printf("\t\"Welfare Check\": %d\n", type8);
printf("\tTreats: %d\n", type9);
printf("\t\"Criminal Mischief\": %d\n", type10);
printf("\t\"Animal Related\": %d\n", type11);
printf("\tInformation: %d\n", type12);


printf("\nPer-division totals:\n");
printf("\tPRUE: %s\n",prue);
printf("\tSOUTH: %s\n",south);
printf("\tWEST: %s\n",west);
printf("\tNORTH: %s\n",north);
printf("\tCENTRAL: %s\n\n",central);
}




