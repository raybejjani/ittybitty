#!/usr/bin/env python
"""builds content lookup files with data contenti for ittybitty"""

import os,hashlib,argparse,time

def get_file_tuples(path=".", base_dir=None, walker=None):
    """returns a list of tuples (file path, file content) for a recursive walk of path"""
    base_dir = path if base_dir == None else base_dir
    walker = os.walk(path, topdown=True, followlinks=True) if walker == None else walker
    accum = []

    for dirname, dirnames, filenames in walker:
        for filename in filenames:
            # on disk path
            file_path = os.path.join(dirname, filename)
            # on server path: relative path to base dir
            http_path = file_path[len(base_dir):]
            # read in file data
            f = open(file_path, 'ro')
            try:
                file_data = f.read()
            finally:
                f.close()
        
            accum.append((http_path, file_data))
        
        for subdirname in dirnames:
            accum.extend(get_file_tuples(path=os.path.join(dirname, subdirname), 
                base_dir=base_dir, walker=walker))
    return accum



content_template_line = "// %s\nstatic const itty_content_t content_md5_%s = {.length = %s, .data = data_md5_%s};"
data_block_template_line = "// %s\nstatic const char data_md5_%s[] = {%s};"
matcher_line_template = '"%s" @{ content = &content_md5_%s; }'
def generate_file(template, files, index_filename):
    """generates a ragel file from the template provided with matchers for all files and i
    an extra "/" for the index file"""

    # code blocks to define the data
    data_blocks = []
    #content structs to point to data
    content_blocks = []
    # matcher lines for each path
    matcher_lines = []

    for file in files:
        md5_hash = hashlib.md5(file[1]).hexdigest()
        file_data = ",".join(["0x%s"%x.encode("hex") for x in file[1]])
        file_data_len = len(file[1])
        if len(file_data) == 0: file_data = '""'

        data_blocks.append(data_block_template_line%(file[0], md5_hash, file_data))
        content_blocks.append(content_template_line%(file[0], md5_hash, file_data_len, md5_hash))
        matcher_lines.append(matcher_line_template%(file[0], md5_hash))
        if index_filename == file[0]:
            matcher_lines.append(matcher_line_template%("/", md5_hash))
    
    ret = template
    ret = ret.replace("###DATABLOCKS###", "\n".join(data_blocks))
    ret = ret.replace("###CONTENTBLOCKS###", "\n".join(content_blocks))
    ret = ret.replace("###MATCHERS###", " | \n".join(matcher_lines))
    ret = ret.replace("###GENDATE###", time.ctime())
    return ret

def parseArgs():
    parser = argparse.ArgumentParser(description="ittyfs: Builder for ittybitty content files")
    parser.add_argument('root', type=str, 
        help="path to root directory of files to be served")
    parser.add_argument('-i', dest='index_name', default="/index.html", type=str, 
        help="server path of file that is the root")
    parser.add_argument('--template', dest='template_file', 
        default="content_matcher.rl.tmpl", type=str, 
        help="template file to be used to generate ragel matcher/content file")
    parser.add_argument('-o', dest='output_name', default="content_matcher.rl", type=str, 
        help="path of output file")

    options,unknownArgs = parser.parse_known_args()
    return options,unknownArgs

if __name__ == "__main__":
    options,unknownArgs = parseArgs()
    print options,unknownArgs

    tmpl_f = open(options.template_file, 'ro')
    tmpl = None
    try:
        tmpl = tmpl_f.read()
    finally:
        tmpl_f.close()

    file_info = get_file_tuples(path=options.root)
    print "Preparing:%s"%([x[0] for x in file_info])
    output = generate_file(tmpl, file_info, options.index_name)

    output_f = open(options.output_name, "wo")
    try:
        output_f.write(output)
    finally:
        output_f.close()





