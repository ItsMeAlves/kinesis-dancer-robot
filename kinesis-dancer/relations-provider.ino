void provideBodyRelationsTo(BodyRelation** arr) {
    // Cleaning array
    for(int i = 0; i < NUM_RELATIONS; i++) {
        arr[i] = NULL;
    }

    float multiplier0[3] = {0,1,0};
    arr[0] = new BodyRelation("ElbowRight", 10, LEFT, multiplier0);

    float multiplier1[3] = {0,1,0};
    arr[1] = new BodyRelation("WristRight", 13, LEFT, multiplier1);
}