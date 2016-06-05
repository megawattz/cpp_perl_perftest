#!/usr/bin/env perl
use strict;
use warnings;

use File::Slurp;

if (!@ARGV)
{
  die "usage: perf.pl <filename of file with lines of text>";
}

my $file_contents = read_file($ARGV[0]);

# Get an array of the lines read in.
my @items = split("[\r\n]+", $file_contents);

my $count = 0;

my $times = int($ARGV[1]);

# Create a hash of the lines (line string as key, incrementing number as value). 
# (We aren't timing the creation of the hash map, just the access performance)
my %haystack = map { $_ => $count++ } @items;

print "\n", scalar @items, " lines\n";

print "find by hash\n";
my $mark = time;
for (my $i =0; $i < $times; ++$i)
{
  # refind every needle in the hash
  for my $needle (@items)
  {
    # assignment to make sure perl doesn't optimize out a noop.
    my $thing = $haystack{$needle};
  }
}
my $lap = time;
print "hash: ", $lap - $mark, " seconds\n";

print "find using index (perl strstr)\n";
$mark = time;
for (my $i =0; $i < $times; ++$i)
{
  #refind every needle with index
  for my $needle (@items)
  {
    my $i = index($file_contents, $needle);
  }
}
$lap = time;
print "index: ", $lap - $mark, " seconds\n";

#
# $Id: perf.pl 2596 2012-11-09 19:01:24Z whoward $
#
