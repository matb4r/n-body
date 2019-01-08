void SerialApplyFoo( float a[], size_t n ) {
	for( size_t i=0; i!=n; ++i )
		Foo(a[i]);
}