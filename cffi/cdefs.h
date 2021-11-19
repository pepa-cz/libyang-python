/*
 * Copyright (c) 2018-2019 Robin Jarry
 * SPDX-License-Identifier: MIT
 */
struct ly_ctx;

#define	LY_CTX_ALL_IMPLEMENTED ...
#define LY_CTX_REF_IMPLEMENTED ...
#define LY_CTX_NO_YANGLIBRARY ...
#define	LY_CTX_DISABLE_SEARCHDIRS   ...
#define LY_CTX_DISABLE_SEARCHDIR_CWD ...
#define	LY_CTX_PREFER_SEARCHDIRS ...
#define LY_CTX_ENABLE_IMP_FEATURES ...
#define LY_CTX_EXPLICIT_COMPILE ...
#define LY_CTX_REF_IMPLEMENTED ...
#define LY_CTX_SET_PRIV_PARSED ...


typedef enum {
    LY_SUCCESS,
    LY_EMEM,
    LY_ESYS,
    LY_EINVAL,
    LY_EEXIST,
    LY_ENOTFOUND,
    LY_EINT,
    LY_EVALID,
    LY_EDENIED,
    LY_EINCOMPLETE,
    LY_ERECOMPILE,
    LY_ENOT,
    LY_EOTHER,
    LY_EPLUGIN = 128
} LY_ERR;

LY_ERR ly_ctx_new(const char *, uint16_t, struct ly_ctx **);
void ly_ctx_destroy(struct ly_ctx *);
int ly_ctx_set_searchdir(struct ly_ctx *, const char *);

typedef enum
{
	LY_TYPE_UNKNOWN = 0,
	LY_TYPE_BINARY,
	LY_TYPE_UINT8,
	LY_TYPE_UINT16,
	LY_TYPE_UINT32,
	LY_TYPE_UINT64,
	LY_TYPE_STRING,
	LY_TYPE_BITS,
	LY_TYPE_BOOL,
	LY_TYPE_DEC64,
	LY_TYPE_EMPTY,
	LY_TYPE_ENUM,
	LY_TYPE_IDENT,
	LY_TYPE_INST,
	LY_TYPE_LEAFREF,
	LY_TYPE_UNION,
	LY_TYPE_INT8,
	LY_TYPE_INT16,
	LY_TYPE_INT32,
	LY_TYPE_INT64
} LY_DATA_TYPE;

typedef enum {
	LY_LLERR,
	LY_LLWRN,
	LY_LLVRB,
	LY_LLDBG,
	...
} LY_LOG_LEVEL;

typedef enum {
    LYVE_SUCCESS,
    LYVE_SYNTAX,
    LYVE_SYNTAX_YANG,
    LYVE_SYNTAX_YIN,
    LYVE_REFERENCE,
    LYVE_XPATH,
    LYVE_SEMANTICS,
    LYVE_SYNTAX_XML,
    LYVE_SYNTAX_JSON,
    LYVE_DATA,
    LYVE_OTHER
} LY_VECODE;

#define LY_LOLOG ...
#define LY_LOSTORE ...
#define LY_LOSTORE_LAST ...
int ly_log_options(int);

LY_LOG_LEVEL ly_log_level(LY_LOG_LEVEL);
extern "Python" void lypy_log_cb(LY_LOG_LEVEL, const char *, const char *);
void ly_set_log_clb(void (*)(LY_LOG_LEVEL, const char *, const char *), int);
struct ly_err_item *ly_err_first(const struct ly_ctx *);
void ly_err_clean(struct ly_ctx *, struct ly_err_item *);
LY_VECODE ly_vecode(const struct ly_ctx *);

#define LYS_UNKNOWN ...
#define LYS_CONTAINER ...
#define LYS_CHOICE ...
#define LYS_LEAF ...
#define LYS_LEAFLIST ...
#define LYS_LIST ...
#define LYS_ANYXML ...
#define LYS_ANYDATA ...
#define LYS_CASE ...
#define LYS_RPC ...
#define LYS_ACTION ...
#define LYS_NOTIF ...
#define LYS_USES ...
#define LYS_INPUT ...
#define LYS_OUTPUT ...
#define LYS_GROUPING ...
#define LYS_AUGMENT ...

struct lys_module* ly_ctx_load_module(struct ly_ctx *, const char *, const char *, const char **);
struct lys_module* ly_ctx_get_module(const struct ly_ctx *, const char *, const char *);
struct lys_module* ly_ctx_get_module_iter(const struct ly_ctx *, uint32_t *);

LY_ERR lys_find_xpath(const struct ly_ctx *, const struct lysc_node *, const char *, uint32_t, struct ly_set **);
void ly_set_free(struct ly_set *, void(*)(void *obj));

struct ly_set {
	uint32_t size;
	uint32_t count;
    union {
        struct lyd_node **dnodes;
        struct lysc_node **snodes;
        void **objs;
    };
};

struct lysc_node {
    uint16_t nodetype;
    uint16_t flags;
    struct lys_module *module;
    struct lysc_node *parent;
    struct lysc_node *next;
    struct lysc_node *prev;
    const char *name;
    const char *dsc;
    const char *ref;
    void *priv;
    ...;
};

struct ly_err_item {
    LY_LOG_LEVEL level;
    LY_ERR no;
    LY_VECODE vecode;
    char *msg;
    char *path;
    char *apptag;
    struct ly_err_item *next;
    struct ly_err_item *prev;
    ...;
};

struct lyd_node {
    uint32_t hash;
    uint32_t flags;
    const struct lysc_node *schema;
    struct lyd_node_inner *parent;
    struct lyd_node *next;
    struct lyd_node *prev;
    struct lyd_meta *meta;
    void *priv;
};

LY_ERR lys_set_implemented(struct lys_module *,	const char **);

#define LYD_NEW_PATH_UPDATE ...
#define LYD_NEW_PATH_OUTPUT ...
#define LYD_NEW_PATH_OPAQ   ...
#define LYD_NEW_PATH_BIN_VALUE ...
#define LYD_NEW_PATH_CANON_VALUE ...
LY_ERR lyd_new_path(struct lyd_node *, const struct ly_ctx *, const char *, const char *, uint32_t, struct lyd_node **);
LY_ERR lyd_find_xpath(const struct lyd_node *, const char *, struct ly_set **);
void lyd_free_all(struct lyd_node *node);
void lyd_free_tree(struct lyd_node *node);

typedef enum {
    LYD_UNKNOWN,
    LYD_XML,
    LYD_JSON,
    LYD_LYB
} LYD_FORMAT;

enum lyd_type {
    LYD_TYPE_DATA_YANG,
    LYD_TYPE_RPC_YANG,
    LYD_TYPE_NOTIF_YANG,
    LYD_TYPE_REPLY_YANG,
    LYD_TYPE_RPC_NETCONF,
    LYD_TYPE_NOTIF_NETCONF,
    LYD_TYPE_REPLY_NETCONF
};

#define LYD_PRINT_KEEPEMPTYCONT ...
#define LYD_PRINT_SHRINK   ...
#define LYD_PRINT_WD_ALL ...
#define LYD_PRINT_WD_ALL_TAG ...
#define LYD_PRINT_WD_EXPLICIT ...
#define LYD_PRINT_WD_IMPL_TAG ...
#define LYD_PRINT_WD_MASK ...
#define LYD_PRINT_WITHSIBLINGS ...
#define LYD_PRINT_WD_TRIM ...
LY_ERR lyd_print_mem(char **, const struct lyd_node *, LYD_FORMAT, uint32_t);
LY_ERR lyd_print_tree(struct ly_out *, const struct lyd_node *, LYD_FORMAT, uint32_t);
LY_ERR lyd_print_all(struct ly_out *, const struct lyd_node *, LYD_FORMAT, uint32_t);

#define LYD_PARSE_LYB_MOD_UPDATE ...
#define LYD_PARSE_NO_STATE ...
#define LYD_PARSE_ONLY ...
#define LYD_PARSE_OPAQ ...
#define LYD_PARSE_OPTS_MASK ...
#define LYD_PARSE_ORDERED ...
#define LYD_PARSE_STRICT ...

#define LYD_VALIDATE_NO_STATE ...
#define LYD_VALIDATE_PRESENT ...
#define LYD_VALIDATE_OPTS_MASK ...

LY_ERR lyd_parse_data_mem(const struct ly_ctx *, const char *, LYD_FORMAT, uint32_t, uint32_t, struct lyd_node **);

struct ly_in;
struct ly_out;
typedef uint8_t ly_bool;
void ly_in_free(struct ly_in *, ly_bool);
void ly_out_free(struct ly_out *, void(*)(void *arg), ly_bool);
LY_ERR ly_in_new_memory(const char *, struct ly_in **);
LY_ERR ly_in_new_filepath(const char *, size_t, struct ly_in **);
LY_ERR ly_in_new_fd(int, struct ly_in **);
LY_ERR ly_in_new_file(FILE *, struct ly_in **);
LY_ERR ly_out_new_memory(char **, size_t, struct ly_out **);
LY_ERR ly_out_new_filepath(const char *, struct ly_out **);
LY_ERR ly_out_new_file(FILE *, struct ly_out **);
LY_ERR ly_out_new_fd(int, struct ly_out **);

LY_ERR lyd_parse_data(const struct ly_ctx *, struct lyd_node *, struct ly_in *, LYD_FORMAT, uint32_t, uint32_t, struct lyd_node **);
LY_ERR lyd_parse_op(const struct ly_ctx *, struct lyd_node *, struct ly_in *, LYD_FORMAT, enum lyd_type, struct lyd_node **, struct lyd_node **);

typedef enum {
   LYS_OUT_UNKNOWN,
   LYS_OUT_YANG,
   LYS_OUT_YANG_COMPILED,
   LYS_OUT_YIN,
   LYS_OUT_TREE
} LYS_OUTFORMAT;

LY_ERR lys_print_mem(char **, const struct lys_module *, LYS_OUTFORMAT, uint32_t);
LY_ERR lys_print_module(struct ly_out *, const struct lys_module *, LYS_OUTFORMAT, size_t, uint32_t);

#define LYS_PRINT_NO_SUBSTMT ...
#define LYS_PRINT_SHRINK ...

struct lys_module {
    const char *name;
    const char *revision;
    const char *ns;
    const char *prefix;
    const char *filepath;
    const char *org;
    const char *contact;
    const char *dsc;
    const char *ref;
    struct lysp_module *parsed;
    struct lysc_module *compiled;
    struct lysc_ident *identities;
    struct lys_module **augmented_by;
    struct lys_module **deviated_by;
    ly_bool implemented;
    ly_bool to_compile;
    uint8_t latest_revision;
    ...;
};

struct lysp_module {
    struct lys_module *mod;
    struct lysp_revision *revs;
    struct lysp_import *imports;
    struct lysp_include *includes;
    struct lysp_ext *extensions;
    struct lysp_feature *features;
    struct lysp_ident *identities;
    struct lysp_tpdf *typedefs;
    struct lysp_node_grp *groupings;
    struct lysp_node *data;
    struct lysp_node_augment *augments;
    struct lysp_node_action *rpcs;
    struct lysp_node_notif *notifs;
    struct lysp_deviation *deviations;
    struct lysp_ext_instance *exts;
    uint8_t version;
    uint8_t parsing : 1;
    uint8_t is_submod : 1;
};

const struct lysc_node *lys_getnext(const struct lysc_node *, const struct lysc_node *, const struct lysc_module *, uint32_t);

struct lysc_node_container {
    union {
        struct lysc_node node;
        struct {
            uint16_t nodetype;
            uint16_t flags;
            struct lys_module *module;
            struct lysc_node *parent;
            struct lysc_node *next;
            struct lysc_node *prev;
            const char *name;
            const char *dsc;
            const char *ref;
            struct lysc_ext_instance *exts;
            void *priv;
            ...;
        };
    };

    struct lysc_node *child;
    struct lysc_must *musts;
    struct lysc_when **when;
    struct lysc_node_action *actions;
    struct lysc_node_notif *notifs;
};

struct lysp_feature {
    const char *name;
    struct lysp_qname *iffeatures;
    struct lysc_iffeature *iffeatures_c;
    struct lysp_feature **depfeatures;
    const char *dsc;
    const char *ref;
    struct lysp_ext_instance *exts;
    uint16_t flags;
};

LY_ERR lys_feature_value(const struct lys_module *, const char *);
struct lysp_feature* lysp_feature_next(const struct lysp_feature *, const struct lysp_module *, uint32_t *);

#define LYS_CONFIG_W ...
#define LYS_CONFIG_R ...
#define LYS_CONFIG_MASK ...
#define LYS_STATUS_CURR ...
#define LYS_STATUS_DEPRC ...
#define LYS_STATUS_OBSLT ...
#define LYS_STATUS_MASK ...
#define LYS_MAND_TRUE ...
#define LYS_MAND_FALSE ...
#define LYS_MAND_MASK ...
#define LYS_PRESENCE ...
#define LYS_UNIQUE ...
#define LYS_KEY ...
#define LYS_KEYLESS ...
#define LYS_FENABLED ...
#define LYS_ORDBY_SYSTEM ...
#define LYS_ORDBY_USER ...
#define LYS_ORDBY_MASK ...
#define LYS_YINELEM_TRUE ...
#define LYS_YINELEM_FALSE ...
#define LYS_YINELEM_MASK ...
#define LYS_USED_GRP ...
#define LYS_SET_VALUE ...
#define LYS_SET_MIN ...
#define LYS_SET_MAX ...
#define LYS_SET_BASE ...
#define LYS_SET_BIT ...
#define LYS_SET_ENUM ...
#define LYS_SET_FRDIGITS ...
#define LYS_SET_LENGTH ...
#define LYS_SET_PATH ...
#define LYS_SET_PATTERN ...
#define LYS_SET_RANGE ...
#define LYS_SET_TYPE ...
#define LYS_SET_REQINST ...
#define LYS_SET_DFLT ...
#define LYS_SET_UNITS ...
#define LYS_SET_CONFIG ...
#define LYS_SINGLEQUOTED ...
#define LYS_DOUBLEQUOTED ...
#define LYS_YIN_ATTR ...
#define LYS_YIN_ARGUMENT ...
#define LYS_INTERNAL ...
#define LYS_IS_ENUM ...
#define LYS_IS_INPUT ...
#define LYS_IS_OUTPUT ...
#define LYS_IS_NOTIF ...

#define LY_REV_SIZE 11

struct lysp_revision {
    char date[LY_REV_SIZE];
    const char *dsc;
    const char *ref;
    struct lysp_ext_instance *exts;
};

typedef enum {
    LYSC_PATH_LOG,
    LYSC_PATH_DATA
} LYSC_PATH_TYPE;

char* lysc_path(const struct lysc_node *, LYSC_PATH_TYPE, char *, size_t);

struct lysp_node_container {
    struct lysp_restr *musts;
    struct lysp_when *when;
    const char *presence;
    struct lysp_tpdf *typedefs;
    struct lysp_node_grp *groupings;
    struct lysp_node *child;
    struct lysp_node_action *actions;
    struct lysp_node_notif *notifs;
    ...;
};

struct lysc_node_leaf {
    union {
        struct lysc_node node;
        struct {
            void *priv;
            uint16_t flags;
            ...;
        };
    };
    struct lysc_must *musts;
    struct lysc_when **when;
    struct lysc_type *type;
    const char *units;
    struct lyd_value *dflt;
    ...;
};

struct lysp_node_leaf {
    struct lysp_restr *musts;
    struct lysp_when *when;
    struct lysp_type type;
    const char *units;
    struct lysp_qname dflt;
    ...;
};

struct lysc_node_list {
    struct lysc_node *child;
    struct lysc_must *musts;
    struct lysc_when **when;
    struct lysc_node_action *actions;
    struct lysc_node_notif *notifs;
    struct lysc_node_leaf ***uniques;
    uint32_t min;
    uint32_t max;
    ...;
};

struct lysc_node_leaflist {
    struct lysc_must *musts;
    struct lysc_when **when;
    struct lysc_type *type;
    const char *units;
    struct lyd_value **dflts;
    uint32_t min;
    uint32_t max;
    ...;
};

struct lysp_node_leaflist {
    struct lysp_restr *musts;
    struct lysp_when *when;
    struct lysp_type type;
    const char *units;
    struct lysp_qname *dflts;
    uint32_t min;
    uint32_t max;
    ...;
};

struct lysp_node_list {
    struct lysp_restr *musts;
    struct lysp_when *when;
    const char *key;
    struct lysp_tpdf *typedefs;
    struct lysp_node_grp *groupings;
    struct lysp_node *child;
    struct lysp_node_action *actions;
    struct lysp_node_notif *notifs;
    struct lysp_qname *uniques;
    uint32_t min;
    uint32_t max;
    ...;
};

struct lysc_type {
    struct lysc_ext_instance *exts;
    struct lyplg_type *plugin;
    LY_DATA_TYPE basetype;
    uint32_t refcount;
};

struct lysp_type {
    const char *name;
    struct lysp_restr *range;
    struct lysp_restr *length;
    struct lysp_restr *patterns;
    struct lysp_type_enum *enums;
    struct lysp_type_enum *bits;
    struct lyxp_expr *path;
    const char **bases;
    struct lysp_type *types;
    struct lysp_ext_instance *exts;
    const struct lysp_module *pmod;
    struct lysc_type *compiled;
    uint8_t fraction_digits;
    uint8_t require_instance;
    uint16_t flags;
};

struct lysp_qname {
    const char *str;
    const struct lysp_module *mod;
};

struct lysc_type_union {
    struct lysc_ext_instance *exts;
    struct lyplg_type *plugin;
    LY_DATA_TYPE basetype;
    uint32_t refcount;
    struct lysc_type **types;
};

struct lysc_type_enum {
    struct lysc_ext_instance *exts;
    struct lyplg_type *plugin;
    LY_DATA_TYPE basetype;
    uint32_t refcount;
    struct lysc_type_bitenum_item *enums;
};

struct lysc_type_bits {
    struct lysc_ext_instance *exts;
    struct lyplg_type *plugin;
    LY_DATA_TYPE basetype;
    uint32_t refcount;
    struct lysc_type_bitenum_item *bits;
};

struct lysc_type_bitenum_item {
    const char *name;
    const char *dsc;
    const char *ref;
    struct lysc_ext_instance *exts;
    union {
        int32_t value;
        uint32_t position;
    };
    uint16_t flags;
};

struct lysp_node {
    struct lysp_node *parent;
    uint16_t nodetype;
    uint16_t flags;
    struct lysp_node *next;
    const char *name;
    const char *dsc;
    const char *ref;
    struct lysp_qname *iffeatures;
    struct lysp_ext_instance *exts;
};

struct lysc_iffeature {
    uint8_t *expr;
    struct lysp_feature **features;
};

/* from libc, needed to free allocated strings */
void free(void *);
