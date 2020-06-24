module.exports = {
  pluginOptions: {
    'style-resources-loader': {
      preProcessor: 'scss',
      patterns: [],
    },
  },
  productionSourceMap: false,
  parallel: true,
  css: { extract: false },
  filenameHashing: false,
  chainWebpack: (config) => {
    config.optimization.delete('splitChunks');
  },
};
