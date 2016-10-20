void provideBodyRelationsTo(BodyRelation** arr) {
    // Cleaning array
    for(int i = 0; i < NUM_RELATIONS; i++) {
        arr[i] = NULL;
    }

    // arr[0] = new BodyRelation("ElbowRight", 7, 512, -3, -1, 0, "HipCenter"); //372
    // // arr[1] = new BodyRelation("WristRight", 12, 1524, 0, 0, -2, "HipCenter");
    // arr[1] = new BodyRelation("ElbowRight", 12, 624, 0, 0, -3, "HipCenter");
    // arr[2] = new BodyRelation("WristRight", 14, 512, 0, 3, 0, "ElbowRight");

    // arr[3] = new BodyRelation("ElbowLeft", 8, 400, 0, 0, 3, "HipCenter");
    // // arr[3] = new BodyRelation("WristLeft", 8, -500, 0, 0, -2, "HipCenter");
    // arr[4] = new BodyRelation("ElbowLeft", 11, 512, -3, 1, 0, "HipCenter"); //652
    // arr[5] = new BodyRelation("WristLeft", 18, 512, 0, -3, 0, "ElbowLeft");

    // arr[6] = new BodyRelation("Head", 3, 512, 2.4, 0, 0, "HipCenter");

    arr[0] = new BodyRelation("ElbowRight", 7, 490, -3, -1, 0, "HipCenter"); //420
    // arr[1] = new BodyRelation("WristRight", 12, 1524, 0, 0, -2, "HipCenter");
    arr[1] = new BodyRelation("ElbowRight", 12, 624, 0, 0, -3.2, "HipCenter");
    arr[2] = new BodyRelation("WristRight", 14, 512, 0, 3, 0, "ElbowRight");

    arr[3] = new BodyRelation("ElbowLeft", 8, 400, 0, 0, 3.2, "HipCenter");
    // arr[3] = new BodyRelation("WristLeft", 8, -500, 0, 0, -2, "HipCenter");
    arr[4] = new BodyRelation("ElbowLeft", 11, 534, -3, 1, 0, "HipCenter"); //604
    arr[5] = new BodyRelation("WristLeft", 18, 512, 0, -3, 0, "ElbowLeft");

    arr[6] = new BodyRelation("Head", 3, 512, 2.4, 0, 0, "HipCenter");
}