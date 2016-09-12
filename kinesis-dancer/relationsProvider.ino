void provideBodyRelationsTo(BodyRelation** arr) {
    // Cleaning array
    for(int i = 0; i < NUM_RELATIONS; i++) {
        arr[i] = NULL;
    }

    float mapper0[3] = {0,1,0};
    arr[0] = new BodyRelation("ElbowRight", 10, LEFT, mapper0);

    float mapper1[3] = {0,1,0};
    arr[1] = new BodyRelation("WristRight", 13, LEFT, mapper1);
}