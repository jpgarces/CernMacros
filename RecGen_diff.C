void RecGen_diff(){
  FILE *f1 = fopen("muon_vcoord_gen.txt");
  FILE *f2 = fopen("muon_vcoord_rec.txt");
  FILE *f3 = fopen("muon_vcoord_track.txt");

  

  fclose(f1);
  fclose(f2);
  fclose(f3);
}
