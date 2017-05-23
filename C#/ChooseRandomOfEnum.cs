//Choose random out of enum

 private enum Type
    {
        TypeA,
        TypeB,
        TypeC,
        TypeD,
        TypeE
    };

    private Type currentType;


    static T RandomEnumValue<T>()
    {
        var type = Enum.GetValues(typeof(T));
        return (T)type.GetValue(new System.Random().Next(type.Length));
    }

 	void Init () {
        currentType =  RandomEnumValue<Type>();
	}