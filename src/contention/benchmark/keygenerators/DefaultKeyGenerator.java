package contention.benchmark.keygenerators;

import contention.abstractions.Distribution;
import contention.abstractions.KeyGenerator;
import contention.benchmark.keygenerators.data.KeyGeneratorData;

public class DefaultKeyGenerator implements KeyGenerator {
    private final KeyGeneratorData data;
    private final Distribution distribution;

    public DefaultKeyGenerator(KeyGeneratorData data, Distribution distribution) {
        this.data = data;
        this.distribution = distribution;
    }

    private int next() {
        int index = distribution.next();
        return data.get(index);
    }

    @Override
    public int nextGet() {
        return next();
    }

    @Override
    public int nextInsert() {
        return next();
    }

    @Override
    public int nextRemove() {
        return next();
    }

    @Override
    public int nextPrefill() {
        return next();
    }
}
