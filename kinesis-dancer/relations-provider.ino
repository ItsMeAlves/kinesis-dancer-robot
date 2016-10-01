void provideBodyRelationsTo(BodyRelation** arr) {
    // Cleaning array
    for(int i = 0; i < NUM_RELATIONS; i++) {
        arr[i] = NULL;
    }

    arr[0] = new BodyRelation("ElbowRight", 7, 400, 0, -2, 0);
    arr[1] = new BodyRelation("ElbowRight", 12, 512, 0, 0, -4);
    arr[2] = new BodyRelation("WristRight", 14, 512, 0, 1, 0);
}